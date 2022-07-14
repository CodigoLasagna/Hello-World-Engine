#include "HelloWorldEngine.h" 
#include <curses.h>

Instance::Instance(){}

Instance::Instance(double x, double y, chtype sprite) :
m_coordx(x), m_coordy(y), m_sprite(sprite){}

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

Instance::~Instance(){}

Renderer::Renderer(){
	m_old_time = clock();
	
	load_curses();
	getmaxyx(stdscr, m_term_height, m_term_width);
	
	m_new_time = clock();
	m_dt = (m_new_time - m_old_time) * m_frame_rate;
}

Renderer::Renderer(int type): m_type(type){
	load_curses();
	getmaxyx(stdscr, m_term_height, m_term_width);
	if (m_type == 0 || m_type == 1){
		m_old_time = clock();
		m_new_time = clock();
		m_dt = (m_new_time - m_old_time) * m_frame_rate;
	}
}

Renderer::Renderer(int type, int wtime): m_type(type), m_wtime(wtime){
	load_curses();
	getmaxyx(stdscr, m_term_height, m_term_width);
	if (m_type == 0 || m_type == 1){
		m_old_time = clock();
		m_new_time = clock();
		m_dt = (m_new_time - m_old_time) * m_frame_rate;
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
}

void Renderer::start_renderer(){
	clear();
	erase();
	if (m_type == 0 ){
		m_old_time = m_new_time;
	}else if (m_type == 1){
		std::this_thread::sleep_for(std::chrono::milliseconds(m_wtime));
		m_old_time = m_new_time;
	}else{
	}
}

void Renderer::update_renderer(){
	if (m_type == 0 || m_type == 1){
		m_new_time = clock();
		m_dt = (m_new_time - m_old_time) * m_frame_rate;
		update_panels();
		doupdate();
	}else{
		char ch{};
		while (ch != 'a') {
			ch = getch();
		}
		update_panels();
		doupdate();
	}
	refresh();
}

int Renderer::get_rtype(){
	return m_type;
}

double Renderer::get_dt(){
	return m_dt;
}
void Renderer::update_env_size(){
	getmaxyx(stdscr, m_term_height, m_term_width);
}

int Renderer::get_term_size(char name){
	if (name == 'w'){
		return m_term_width;
	}else if (name == 'h'){
		return m_term_height;
	}
	return 0;
}

Window::Window(int width, int height, int x, int y, bool fix):
	m_width(width), m_height(height), m_x(x), m_y(y){
	getmaxyx(stdscr, term_h, term_w);
	if (fix == false){
		win = newwin(m_height, m_width, m_y+int(term_h/2)-(m_height/2), m_x+int(term_w/2)-(m_width/2));
	}else{
		win = newwin(m_height, m_width, m_y, m_x);
	}
	pane = new_panel(win);
	clean();
}
void Window::show(bool s){
	if (s == true){
		show_panel(pane);
	}else{
		hide_panel(pane);
	}
}
void Window::clean(){
	getmaxyx(stdscr, term_h, term_w);
	werase(win);
	mvwin(win, m_y+int(term_h/2)-(m_height/2), m_x+int(term_w/2)-(m_width/2));
	wresize(win, m_height, m_width);
	init_pair(m_fgcolor, m_fgcolor, m_bgcolor);
	if (term_h < m_height+2 || term_w < m_width+2){
		show(false);
	}else{
		show(true);
	}
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

void Instance::set_color(int fg, int bg, bool alt){
	m_fgcolor = fg;
	m_bgcolor = bg;
}
Instance* instance_create(int x, int y, chtype sprite){
	return new Instance(x, y, sprite);
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
		mvwaddch(place.win, temp_y, temp_x, s);
		wattroff(place.win, COLOR_PAIR(instance->m_fgcolor));
	}else{
		wattron(place.win, A_BOLD | COLOR_PAIR(instance->m_fgcolor));
		mvwaddch(place.win, temp_y, temp_x, s);
		wattroff(place.win, A_BOLD | COLOR_PAIR(instance->m_fgcolor));
	}
}
