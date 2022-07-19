//nr
#include "../HelloWorldEngine.h"
#include <curses.h>
#include <string>
int grid[9]{};
int turn{};
int x{0}, y{0};
std::string input{};

void draw();
void contMode(int mode);
void makeInput();
void computer();
Renderer* mainrender = new Renderer(1, 21, 11, 100);
Window mainwin = Window(21, 11, 0, 0, false, mainrender);
Window table = Window(17, 9, 2, 1, false, mainrender);
Window inputWin = Window(21, 3, 0, 6, false, mainrender);

int key{};
int mode{1};

int main(){
	for (int i = 0; i < 9; ++i) grid[i] = -1;
	while (key != int('q')) {
		mainrender->start_renderer();
		mainwin.clean();
		table.clean();
		inputWin.clean();
		key = getch();
		contMode(mode);
		draw();
		mainrender->update_renderer();
	}
	endwin();
	return 0;
}

void draw(){
	for (int i = 0; i < 3; ++i) mvwprintw(mainwin.win, 3+(i*3), 2, "%i", i+1);
	for (int i = 0; i < 11; ++i){
		if ((i%2) == 0) ++y, x = 0;
		if (y == 2 || y == 4) mvwaddch(table.win, 1+y, 5+(x*6), ACS_PLUS); else if ( i < 10) mvwaddch(table.win, 1+y, 5+(x*6), ACS_VLINE);
		for (int j = 0; j < 2; ++j) if ((i%6) != 2) mvwaddch(table.win, 3+(j*2), 3+i, ACS_HLINE);
		x++;
	}
	x = 0; y = 0;
	mvwaddch(table.win, 8, 0, ACS_BTEE);
	mvwaddch(table.win, 0, 16, ACS_RTEE);
	mvwaddch(inputWin.win, 0, 0, ACS_LTEE);
	mvwaddch(inputWin.win, 0, 4, ACS_BTEE);
	mvwaddch(inputWin.win, 0, 20, ACS_RTEE);
	mvwprintw(mainwin.win, 1, 2, "    A     B     C");
	for (int i = 0; i < 9; ++i){
		if ((i%3) == 0) ++y, x = 0;
		switch (grid[i]) {
			case -1:mvwaddch(table.win, (y*2), 3+(x*5), ' ');break;
			case 0:mvwaddch(table.win, (y*2), 3+(x*5), 'X');break;
			case 1:mvwaddch(table.win, (y*2), 3+(x*5), 'O');break;
		}
		x++;
	}
	mvwprintw(inputWin.win, 1, 1, "%s", input.c_str());
	x = 0; y = 0;
}

void contMode(int mode){
	switch (mode) {
		case 0:
			makeInput();
		break;
		case 1:
			makeInput();
			if (turn == 1){
				draw();update_panels();doupdate();
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				grid[2] = turn;
				turn = !turn;
			}
		break;
	}
}
void makeInput(){
	MEVENT event;
	mousemask(BUTTON1_CLICKED, NULL);
	int p{}, mx_lb{}, mx_db{}, my_lb{}, my_db{};
	mx_lb = (mainrender->get_term_size('w')/2)-(table.m_width/2)+2; mx_db = (mainrender->get_term_size('w')/2)+(table.m_width/2)+2;
	my_lb = (mainrender->get_term_size('h')/2)-(table.m_height/2)+1; my_db = (mainrender->get_term_size('h')/2)+(table.m_height/2)+1;
	if (key == KEY_MOUSE && getmouse(&event) == OK){
		if (event.bstate & BUTTON1_CLICKED){
			int mx{(event.x-mx_lb)/6}, my{((event.y-my_lb)/2)-1};
			if (event.x > mx_lb && event.x < mx_db && event.y > my_lb && event.y < my_db && grid[my*3+mx] == -1){
				grid[my*3+mx] = turn;
				turn = !turn;
			}
		}
	}
	if (key == '\n'){
		if (input.length() > 0) p = std::stoi(input)-1;
		if (grid[p] == -1){
			switch (input.length()) {
				case 0:break;
				case 1:grid[p] = turn;break;
			}
			turn = !turn;
		}
		input = "";
	}
	if (input.length() < 4 && key != EOF && key && key != '\n' && key != KEY_MOUSE){
		if (key != KEY_BACKSPACE && input.length() < 3){
			input += (char)key;
		}else if (input.length() > 0 && key == KEY_BACKSPACE){
			input.pop_back();
		}
	}
}
void computer(){
	for (int i = 0; i < 9; ++i){
		if (grid[i] == -1){

		}
	}
}
