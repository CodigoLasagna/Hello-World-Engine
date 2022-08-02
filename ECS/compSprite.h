#pragma once

#ifndef COMP_SPRITE
#define COMP_SPRITE

#include "compPosition.h"
#include <ncurses.h>

class SpriteComponent : public Component{
private:
	PositionComponent *position;
	const char* sprite{"#"};
	int temp_x{}, temp_y{};
	int fgc{}, bgc{-1};
	bool bc{};
	WINDOW* window;
public:
	SpriteComponent() = default;
	SpriteComponent(const char* s, WINDOW* sWin){
		setSprite(s);
		window = sWin;
	}
	
	void setSprite(const char* s){
		sprite = s;
	}
	
	void setColor(int fg_c, int bg_c, bool bc_c){
		fgc = fg_c, bgc = bg_c, bc = bc_c;
	}
	
	void init() override{
		position = &entity->getComponent<PositionComponent>();
	}
	
	void update() override{
		temp_x = position->x();
		temp_y = position->y();
	}
	
	void draw() override{
		init_pair(fgc, fgc, bgc);
		if (bc == false){
			wattron(window, COLOR_PAIR(fgc));
			mvwprintw(window, temp_y, temp_x, "%s", sprite);
			wattroff(window, COLOR_PAIR(fgc));
		}else{
			wattron(window, A_BOLD | COLOR_PAIR(fgc));
			mvwprintw(window, temp_y, temp_x, "%s", sprite);
			wattroff(window, A_BOLD | COLOR_PAIR(fgc));
		}
	}
};

#endif
