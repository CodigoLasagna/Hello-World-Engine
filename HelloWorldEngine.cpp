#include "HelloWorldEngine.h" 

Instance::Instance(){}

Instance::Instance(double x, double y, char sprite) :
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

char Instance::get_sprite(){
	return m_sprite;
}
void Instance::set_sprite(char new_sprite){
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
}

void Renderer::start_renderer(){
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
	m_width(width), m_height(height){
	getmaxyx(stdscr, term_h, term_w);
	if (fix == false){
		win = newwin(m_height, m_width, y+int(term_h/2)-(m_height/2), x+int(term_w/2)-(m_width/2));
	}else{
		win = newwin(m_height, m_width, y, x);
	}
	pane = new_panel(win);
	box(win, 0, 0);
}
void Window::init(){
	fixate();
	box(win, 0, 0);
}
void Window::init(int w, int h){
	fixate();
	win = newwin(h, w, 0, 0);
	pane = new_panel(win);
	box(win, 0, 0);
}
void Window::show(bool s){
	if (s == true){
		show_panel(pane);
	}else{
		hide_panel(pane);
	}
}
void Window::clean(){
	werase(win);
	box(win, 0, 0);
}
void Window::fixate(){
	getmaxyx(stdscr, term_h, term_w);
	win = newwin(m_height, m_width, int(term_h/2)-(m_height/2), int(term_w/2)-(m_width/2));
	pane = new_panel(win);
}

WINDOW* create_panel(int x, int y, int width, int height){
	WINDOW* win;
	PANEL* panel;
	
	win = newwin(height, width, y, x);
	panel = new_panel(win);
	box(win, 0, 0);
	
	return win;
}

void clear_panel(WINDOW* win){
	werase(win);
	box(win, 0, 0);
}

Instance* instance_create(int x, int y, char sprite){
	return new Instance(x, y, sprite);
}
void instance_destroy(Instance* instance){
	delete instance;
	instance = nullptr;
}

void instance_draw(WINDOW* win, Instance* instance){
	char s{instance->get_sprite()};
	double temp_x{instance->get_coord('x')};
	double temp_y{instance->get_coord('y')};
	mvwprintw(win, temp_y, temp_x, "%c", s);
}
