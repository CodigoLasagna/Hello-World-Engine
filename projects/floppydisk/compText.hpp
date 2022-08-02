//nr 1
#pragma once
#include "ComponentsFloppy.hpp"
#include <curses.h>

class TextComponent : public Component{
private:
	std::string m_text{};
	int m_status{};
	WINDOW* m_window{};
public:
	TextComponent(){
		m_text = "new text";
	}
	TextComponent(WINDOW* window, const char* text){
		m_window = window;
		m_text = text;
		m_status = 1;
	}
	void changeText(const char* text){
		m_text = text;
	}
	void draw() override{
		if (m_status == 0){
			mvwprintw(stdscr, 2, 2, "%s", m_text.c_str());
		}else {
			mvwprintw(m_window, 1, 2, "%s", m_text.c_str());
		}
	}
};
