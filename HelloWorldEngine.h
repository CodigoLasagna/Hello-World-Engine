#ifndef GAME_ENGINE
#define GAME_ENGINE

#include <curses.h> 
#include <panel.h> 
//#include <ncursesw/curses.h> 
//#include <ncursesw/panel.h> 
#include <string> 
#include <chrono>
#include <thread>
#include <iostream>

class Instance{
private:
	bool m_solid{};
	char m_sprite{'#'};
public:
	double m_coordx{};
	double m_coordy{};
	Instance();
	Instance(double x, double y, char sprite);
	double get_coord(char coord);
	void set_coord(char coord, double value);
	
	char get_sprite();
	void set_sprite(char new_sprite);
	
	~Instance();
};

class Renderer{
private:
	int m_term_width{}, m_term_height{};
	int m_wtime{200};
	double m_frame_rate{1.0 / 60.0};
	double m_old_time{}, m_new_time{}, m_dt{};
	int m_type{};	// [type 0 == no_sleeptime] [type 1 == sleeptypem] [type 2 == wait for command]
	void load_curses();
public:
	Renderer();
	Renderer(int type);
	Renderer(int type, int wtime);
	void update_env_size();
	int get_term_size(char name);
	void start_renderer();
	void update_renderer();
	int get_rtype();
	double get_dt();
	~Renderer();
};

class Window{
	private:
		int term_w{}, term_h{};
	public:
		int m_width = 10;
		int m_height = 10;
		WINDOW* win;
		PANEL* pane;
		Window(int width, int height, int x, int y, bool fix);
		void init();
		void init(int w, int h);
		void show(bool s);
		void clean();
		void fixate();
		void create_pane();
		~Window() = default;
};

Instance* instance_create(int x, int y, char sprite);
void instance_destroy(Instance* instance);

void instance_draw(WINDOW*, Instance* instance);

void update();


#endif
