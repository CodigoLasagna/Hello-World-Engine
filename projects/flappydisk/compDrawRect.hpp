//nr 1
#pragma once
#include "ComponentsFloppy.hpp"

class DrawRectComponent : public Component{
private:
	int m_width{}, m_height{}, m_v{1};
	int fgc{}, bgc{-1};
	bool bc{};
	PositionComponent *position;
	WINDOW* m_window;
public:
	DrawRectComponent(){
		m_width = 10;
		m_height = 5;
	}
	DrawRectComponent(int width, int height, WINDOW* window){
		m_width = width;
		m_height = height;
		m_window = window;
	}
	void init() override {
		position = &entity->getComponent<PositionComponent>();
		srand(time(NULL));
	}
	void setColor(int fg_c, int bg_c, bool bc_c){
		fgc = fg_c, bgc = bg_c, bc = bc_c;
	}
	
	void update() override{
		position->x(position->x()-m_v);
		if (position->x() < -2){
			position->x(33);
			position->y((rand()%15)+5);
		}
	}
	void draw() override{
		for (int i = 0; i < m_height; ++i){
			for (int j = 0; j < m_width; ++j){
				if (bc == false){
					wattron(m_window, COLOR_PAIR(fgc));
						if (position->y()-(3+i) > 0)
							mvwaddch(m_window, position->y()-(3+i), position->x()+j, '#');
						if (position->y()+(3+i) < 24)
							mvwaddch(m_window, position->y()+(3+i), position->x()+j, '#');
					wattroff(m_window, COLOR_PAIR(fgc));
				}else{
					wattron(m_window, A_BOLD | COLOR_PAIR(fgc));
						if (position->y()-(3+i) > 0 )
							if (position->x()+j > 0 && position->x()+j < 30)
								mvwaddch(m_window, position->y()-(3+i), position->x()+j, '#');
						if (position->y()+(3+i) < 24)
							if (position->x()+j > 0 && position->x()+j < 30)
								mvwaddch(m_window, position->y()+(3+i), position->x()+j, '#');
					wattroff(m_window, A_BOLD | COLOR_PAIR(fgc));
				}
			}
		}
	}
	
	int width() { return m_width; }
	int height() { return m_height; }
	int v() { return m_v; }
	void width(int width) { m_width = width; }
	void height(int height) { m_height = height; }
	void v(int v){ m_v = v; }
};
