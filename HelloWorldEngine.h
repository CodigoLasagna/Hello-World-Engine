#pragma once

#ifndef GAME_ENGINE
#define GAME_ENGINE

#include <curses.h> 
#include <panel.h> 
//#include <ncursesw/curses.h> 
//#include <ncursesw/panel.h> 
#include <cmath>
#include <chrono>
#include <thread>

#include "ECS/Components.h"

#define C_BLACK		0
#define C_RED		1
#define C_GREEN		2
#define C_YELLOW	3
#define C_BLUE		4
#define C_MAGENTA	5
#define C_CYAN		6
#define C_WHITE		7
void preciseSleep(double seconds);

class Renderer /*Clase para crear el renderizador*/{
private:
	int m_term_width{}, m_term_height{};
	int past_w{}, past_h{};
	int m_wtime{200};
	double m_frame_rate{};
	double m_old_time{}, m_lapsed{}, m_dt{};
	int m_type{};	// [type 0 == no_sleeptime] [type 1 == sleeptypem] [type 2 == wait for command]
	void load_curses();
	int m_exit_key{};
public:
	size_t m_min_width{20}, m_min_height{20};
	int m_key{};
	bool isRunning{};
	Renderer() = default;
	Renderer(int type, size_t minw, size_t minh);
	Renderer(int type, size_t minw, size_t minh, int wtime);
	Renderer(int type, size_t minw, size_t minh, double wtime, int exit_key);
	void check_sizehealth();
	void display_error();
	int get_term_size(char name);
	void start_renderer();
	void game_loop(void update(), void draw());
	void update_renderer();
	int get_rtype();
	double get_dt();
	~Renderer();
};

class Window{
private:
	int term_w{}, term_h{};
	bool change_w{};
public:
	Renderer* mainRender;
	int m_width = 10;
	int m_height = 10;
	int m_x{}, m_y{};
	int m_fgcolor{};
	int m_bgcolor{-1};
	bool m_bcolor{};
	bool m_fix{};
	WINDOW* win;
	PANEL* pane;
	Window() = default;
	Window(int width, int height, int x, int y, bool fix, Renderer* render);
	void show(bool s);
	void clean();
	~Window() = default;
};

class Instance{
private:
	chtype m_sprite{'#'};
public:
	const char* m_assprite{"#"};
	int m_type{};
	double m_coordx{};
	double m_coordy{};
	int m_fgcolor{};
	int m_bgcolor{-1};
	bool m_bcolor{};
	bool m_ascii{};
	Instance() = default;
	Instance(double x, double y, chtype sprite);
	Instance(double x, double y, const char* sprite, bool ascii);
	double get_coord(char coord);
	void set_coord(char coord, double value);
	void set_color(int fg, int bg, bool alt);
	
	chtype get_sprite();
	void set_sprite(chtype new_sprite);
	
	~Instance() = default;
};

class EntityComponentSystem{
private:
public:
	EntityComponentSystem() = default;
	~EntityComponentSystem() = default;
	std::vector<Instance> entities;
};

Instance* instance_create(int x, int y, chtype sprite);
Instance* instance_create(int x, int y, const char* sprite, bool ascii);
void instance_destroy(Instance* instance);
void instance_draw(Window, Instance* instance);

#endif
