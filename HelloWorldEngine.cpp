#include "HelloWorldEngine.h" 
#include <chrono>
#include <curses.h>
#include <ncurses.h>
#include <panel.h>

//Funciones de ventanas
Window::Window(int width, int height, int x, int y, bool fix, Renderer* render):
	m_width(width), m_height(height), m_x(x), m_y(y), m_fix(fix),mainRender(render){
	getmaxyx(stdscr, term_h, term_w);
	if (m_fix == false){
		win = newwin(m_height, m_width, m_y+int(term_h/2)-(m_height/2), m_x+int(term_w/2)-(m_width/2));
		//win = newwin(m_height, m_width, 0, 0);
	}else if (m_fix == true){
		win = newwin(m_height, m_width, 0, 0);
	}
	pane = new_panel(win);
	clean();
}
void Window::show(bool s){
	if (s == true){
		if (change_w == false){
			show_panel(pane);
			change_w = true;
		}
	}else{
		hide_panel(pane);
		change_w = false;
	}
}
void Window::clean(){
	getmaxyx(stdscr, term_h, term_w);
	if (term_h < mainRender->m_min_height && term_w < mainRender->m_min_width){
		show(false);
	}else{
		show(true);
	}
	werase(win);
	if (m_fix == false)
		mvwin(win, m_y+int(term_h/2)-(m_height/2), m_x+int(term_w/2)-(m_width/2));
	wresize(win, m_height, m_width);
	init_pair(m_fgcolor, m_fgcolor, m_bgcolor);
	if (m_bcolor == false){
		wattron(win, COLOR_PAIR(m_fgcolor));
		box(win, 0, 0);
		wattroff(win, COLOR_PAIR(m_fgcolor));
	}else{
		wattron(win, A_BOLD | COLOR_PAIR(m_fgcolor));
		box(win, 0, 0);
		wattroff(win, A_BOLD | COLOR_PAIR(m_fgcolor));
	}
}

//Funciones de render
Renderer::Renderer(int type, size_t minw, size_t minh):
	m_type(type), m_min_width(minw), m_min_height(minh){
	load_curses();
	if (m_type == 0 || m_type == 1){
		m_old_time = clock();
		m_dt = 0.0;
	}
}

Renderer::Renderer(int type, size_t minw, size_t minh,int wtime):
	m_type(type), m_min_width(minw), m_min_height(minh), m_wtime(wtime){
	load_curses();
	if (m_type == 0 || m_type == 1){
		m_old_time = clock();
		m_dt = 0.0;
	}
}

Renderer::Renderer(int type, size_t minw, size_t minh, double wtime, int exit_key):
	m_type(type), m_min_width(minw), m_min_height(minh), m_wtime(double(wtime)), m_exit_key(exit_key){
	load_curses();
	if (m_type == 0 || m_type == 1){
		m_old_time = clock();
		m_dt = 0.0;
	}
}

void Renderer::load_curses(){
	setlocale(LC_ALL, "");
	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);
	nodelay(stdscr, TRUE);
	keypad(stdscr,TRUE);
	use_default_colors();
	start_color();
	init_pair(C_BLACK, C_BLACK, -1);
	init_pair(C_RED, C_RED, -1);
	init_pair(C_GREEN, C_GREEN, -1);
	init_pair(C_YELLOW, C_YELLOW, -1);
	init_pair(C_BLUE, C_BLUE, -1);
	init_pair(C_MAGENTA, C_MAGENTA, -1);
	init_pair(C_CYAN, C_CYAN, -1);
	init_pair(C_WHITE, C_WHITE, -1);
	getmaxyx(stdscr, m_term_height, m_term_width);
	isRunning = true;
	check_sizehealth();
}

void Renderer::start_renderer(){
	getmaxyx(stdscr, m_term_height, m_term_width);
	if (m_term_height != past_h || m_term_width != past_w){
		past_w = m_term_width, past_h = m_term_height;
		clear();
	}
	check_sizehealth();
	if (m_type == 0 ){
	
	}else if (m_type == 1){
		std::this_thread::sleep_for(std::chrono::milliseconds(m_wtime));
		//m_old_time = m_new_time;
	}
}

void Renderer::game_loop(void update(), void draw()){
	update_panels();
	doupdate();
	auto old_time = std::chrono::high_resolution_clock::now();
	while (isRunning == true) {
		getmaxyx(stdscr, m_term_height, m_term_width);
		m_key = getch();if (m_key == m_exit_key) isRunning = false;
		auto new_time = std::chrono::high_resolution_clock::now();
		double dt = (new_time - old_time).count() / 1e9;
		//update here
		if (m_term_height != past_h || m_term_width != past_w){
			past_w = m_term_width, past_h = m_term_height;
			clear();
		}
		check_sizehealth();
		update();
		draw();
		update_panels();
		doupdate();
		auto frame_time = std::chrono::high_resolution_clock::now();
		double sleepSecs = 1.0 / m_wtime - (frame_time - new_time).count() / 1e9;
		preciseSleep(sleepSecs);
		old_time = new_time;
	}
	endwin();
}

void Renderer::check_sizehealth(){
	while (isRunning == true && (m_term_width < m_min_width || m_term_height < m_min_height)) {
		getmaxyx(stdscr, m_term_height, m_term_width);
		if (m_term_height != past_h || m_term_width != past_w){
			past_w = m_term_width, past_h = m_term_height;
			clear();
		}
		m_key = getch();
		if (m_key == m_exit_key) isRunning = false;
		display_error();
	}
}

void Renderer::display_error(){
	mvprintw((m_term_height/2)-3, (m_term_width/2)-11, "Current terminal size.");
	mvprintw((m_term_height/2)-2, (m_term_width/2)-11, "[Width:%i]-[Height:%i]", m_term_width, m_term_height);
	mvprintw((m_term_height/2)+1, (m_term_width/2)-10, "Needed terminal size.");
	mvprintw((m_term_height/2)+2, (m_term_width/2)-11, "[Width:%zu]-[Height:%zu]", m_min_width, m_min_height);
}

void preciseSleep(double seconds){
	static double estimate = 5e-3;
	static double mean = 5e-3;
	static double m2 = 0;
	static int64_t count = 1;
	
	while (seconds > estimate) {
		auto start = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		auto end = std::chrono::high_resolution_clock::now();
		
		double observed = (end - start).count() / 1e9;
		seconds -= observed;
		
		++count;
		double delta = observed - mean;
		mean += delta / count;
		m2 += delta * (observed - mean);
		double stddev = std::sqrt(m2 / (count - 1));
		estimate = mean + stddev;
	}
	
	auto start = std::chrono::high_resolution_clock::now();
	while ((std::chrono::high_resolution_clock::now() - start).count() / 1e9 < seconds);
}


void Renderer::update_renderer(){
	if (m_type == 0 || m_type == 1){
		//m_new_time = clock();
		//m_dt = (m_new_time - m_old_time) * m_frame_rate;
		//if (m_term_width > m_min_width && m_term_height > m_min_height){
			update_panels();
		//}
		doupdate();
	}else if (m_type == 2){
		char ch{};
		while (ch != 'a') {
			ch = getch();
		}
		if (m_term_width > m_min_width || m_term_height > m_min_height){
			update_panels();
		}
		doupdate();
	}
}

int Renderer::get_rtype(){
	return m_type;
}

double Renderer::get_dt(){
	return m_dt;
}

int Renderer::get_term_size(char name){
	if (name == 'w'){
		return m_term_width;
	}else if (name == 'h'){
		return m_term_height;
	}
	return 0;
}

//Funciones de instancias
Instance::Instance(double x, double y, chtype sprite) :
m_coordx(x), m_coordy(y), m_sprite(sprite){}

Instance::Instance(double x, double y, const char* sprite, bool ascii) :
m_coordx(x), m_coordy(y), m_assprite(sprite), m_ascii(ascii){}

double Instance::get_coord(char coord){
	if (coord == 'x'){
		return m_coordx;
	}else if (coord == 'y'){
		return m_coordy;
	}
	return 0;
}
void Instance::set_coord(char coord, double value){
	if (coord == 'x'){
		m_coordx = value;
	}else if (coord == 'y'){
		m_coordy = value;
	}
}

chtype Instance::get_sprite(){
	return m_sprite;
}
void Instance::set_sprite(chtype new_sprite){
	m_sprite = new_sprite;
}

void Instance::set_color(int fg, int bg, bool alt){
	m_fgcolor = fg;
	m_bgcolor = bg;
}
Instance* instance_create(int x, int y, chtype sprite){
	return new Instance(x, y, sprite);
}
Instance* instance_create(int x, int y, const char* sprite, bool ascii){
	return new Instance(x, y, sprite, ascii);
}
void instance_destroy(Instance* instance){
	delete instance;
	instance = nullptr;
}

void instance_draw(Window place, Instance* instance){
	chtype s{instance->get_sprite()};
	double temp_x{instance->get_coord('x')};
	double temp_y{instance->get_coord('y')};
	init_pair(instance->m_fgcolor, instance->m_fgcolor, instance->m_bgcolor);
	if (instance->m_bcolor == false){
		wattron(place.win, COLOR_PAIR(instance->m_fgcolor));
		if (instance->m_ascii == true) {
			mvwprintw(place.win, temp_y, temp_x, "%s", instance->m_assprite);
		}else{
			mvwaddch(place.win, temp_y, temp_x, s);
		}
		wattroff(place.win, COLOR_PAIR(instance->m_fgcolor));
	}else{
		wattron(place.win, A_BOLD | COLOR_PAIR(instance->m_fgcolor));
		if (instance->m_ascii == true) {
			mvwprintw(place.win, temp_y, temp_x, "%s", instance->m_assprite);
		}else{
			mvwaddch(place.win, temp_y, temp_x, s);
		}
		wattroff(place.win, A_BOLD | COLOR_PAIR(instance->m_fgcolor));
	}
}
//Funciones de ECS
