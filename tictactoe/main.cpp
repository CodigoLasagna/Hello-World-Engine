//nr
#include "../HelloWorldEngine.h"

int grid[9]{}, turn{}, key{}, mode{}, cleared{}, win{};
std::string input{}, condition{};
void contMode(), draw(), makeInput(), computer(), start();
int check(), code(int len);
Renderer* mainrender = new Renderer(1, 22, 18, 100);
Window mainwin = Window(21, 11, 0, 0, false, mainrender);
Window table = Window(17, 9, 2, 1, false, mainrender);
Window inputWin = Window(21, 3, 0, 6, false, mainrender);
Window info = Window(21, 3, 0, -6, false, mainrender);

int main(){
	srand(time(NULL));
	start();
	while (key != int('q')) {
		mainrender->start_renderer();
		mainwin.clean(); table.clean();inputWin.clean(); info.clean();
		key = getch();
		if (mode == 0){
			start(), table.show(false);
		}else
			table.show(true);
		mvwprintw(info.win, 1, 4, "%s", condition.c_str());
		if (mode != 0 && win == 0) condition = "  TURNO J"+std::to_string(turn+1);
		check(); contMode(); draw();
		if (key == int('r')){
			mode = 0; cleared = 0;
			win = 0;
		}
		mainrender->update_renderer();
	}
	endwin();
	return 0;
}
void start(){
	if (cleared == 0){
		for (int i = 0; i < 9; ++i) grid[i] = -1;
		cleared = 1;
		turn = (rand()%2);
		input = ""; condition = "MODO DE JUEGO";
	}
}
void draw(){
	mvwaddch(info.win, 2, 0, ACS_LTEE);mvwaddch(info.win, 2, 20, ACS_RTEE);
	mvwaddch(inputWin.win, 0, 0, ACS_LTEE);mvwaddch(table.win, 8, 16, ACS_RTEE);mvwaddch(inputWin.win, 0, 20, ACS_RTEE);
	if (mode != 0){
		mvwaddch(inputWin.win, 0, 4, ACS_BTEE);
		mvwaddch(table.win, 8, 0, ACS_BTEE);mvwaddch(table.win, 0, 16, ACS_RTEE);
		mvwprintw(mainwin.win, 1, 2, "    A     B     C");
		int x{0}, y{0};
		for (int i = 0; i < 3; ++i) mvwprintw(mainwin.win, 3+(i*3), 2, "%i", i+1);
		for (int i = 0; i < 11; ++i){
			if ((i%2) == 0) ++y, x = 0;
			if (y == 2 || y == 4) mvwaddch(table.win, 1+y, 5+(x*6), ACS_PLUS); else if ( i < 10) mvwaddch(table.win, 1+y, 5+(x*6), ACS_VLINE);
			for (int j = 0; j < 2; ++j) if ((i%6) != 2) mvwaddch(table.win, 3+(j*2), 3+i, ACS_HLINE);
			x++;
		}
		x = 0; y = 0;
		for (int i = 0; i < 9; ++i){
			if ((i%3) == 0) ++y, x = 0;
			switch (grid[i]) {
				case -1:mvwaddch(table.win, (y*2), 3+(x*5), ' ');break;
				case 0:mvwaddch(table.win, (y*2), 3+(x*5), 'X');break;
				case 1:mvwaddch(table.win, (y*2), 3+(x*5), 'O');break;
			}
			x++;
		}
	}else{
		mvwprintw(mainwin.win, 2, 5, "[JcJ] - [1]");
		mvwprintw(mainwin.win, 4, 5, "[JcC] - [2]");
		mvwprintw(mainwin.win, 6, 4, "[salir] - [q]");
		mvwprintw(mainwin.win, 8, 1, "[volver al menu][r]");
	}
	mvwprintw(inputWin.win, 1, 1, "%s", input.c_str());
}
void contMode(){
	switch (mode) {
		case 0:
			if (key == int('1')) mode = 1, key = EOF;
			if (key == int('2')) mode = 2, key = EOF;
		case 1:
			makeInput();
		break;
		case 2:
			makeInput();
			if (turn == 1){
				if (mode != 0 && win == 0) condition = "  TURNO J"+std::to_string(turn+1);
				mvwprintw(info.win, 1, 4, "%s", condition.c_str());
				draw();update_panels();doupdate();
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				computer();
				turn = !turn;
			}
		break;
	}
}
void makeInput(){
	MEVENT event; mousemask(BUTTON1_CLICKED, NULL);
	int p{-1}, alp{}, mx_lb{}, mx_db{}, my_lb{}, my_db{};
	mx_lb = (mainrender->get_term_size('w')/2)-(table.m_width/2)+2; mx_db = (mainrender->get_term_size('w')/2)+(table.m_width/2)+2;
	my_lb = (mainrender->get_term_size('h')/2)-(table.m_height/2)+1; my_db = (mainrender->get_term_size('h')/2)+(table.m_height/2)+1;
	if (key == KEY_MOUSE && getmouse(&event) == OK && event.bstate & BUTTON1_CLICKED){
		int mx{(event.x-mx_lb)/6}, my{((event.y-my_lb)/2)-1};
		if (event.x > mx_lb && event.x < mx_db && event.y > my_lb && event.y < my_db && grid[my*3+mx] == -1){
			grid[my*3+mx] = turn, turn = !turn;
		}
	}
	if (key == '\n'){
		if (input.length() > 0){
			switch (input.length()) {
				case 1: if (std::isdigit(input[0])) p = std::stoi(input)-1; break;
				case 2: p = code(1); break;
				case 3: p = code(2); break;
			}
			if (grid[p] == -1 && p != -1) grid[p] = turn, turn = !turn;
			p = -1; input = "";
		}
	}
	if (input.length() < 4 && key != EOF && key && key != '\n' && key != KEY_MOUSE){
		if (key != KEY_BACKSPACE && input.length() < 3){
			input += (char)key;
		}else if (input.length() > 0 && key == KEY_BACKSPACE) input.pop_back();
	}
}
int code(int len){
	int p{};
	if (std::isdigit(input[0])){
		if (tolower(input[len]) == 'a') p = 0;if (tolower(input[len]) == 'b') p = 1;if (tolower(input[len]) == 'c') p = 2;
		return (input[0]-49)*3+p;
	}else{
		if (tolower(input[0]) == 'a') p = 0;if (tolower(input[0]) == 'b') p = 1;if (tolower(input[0]) == 'c') p = 2;
		return (input[1]-49)*3+p;
	}
	return 0;
}
void computer(){
	int p{rand()%9};
	if (grid[p] == -1 && check() == true) grid[p] = turn; else if (check() == true) computer();
}
int check(){
	int cells{};
	for (int i = 0; i < 3; ++i){
		if ((grid[i*3] == !turn && grid[i*3+1] == !turn && grid[i*3+2] == !turn || 
		grid[i] == !turn && grid[i+3] == !turn && grid[i+6] == !turn ||
		grid[i] == !turn && grid[4] == !turn && grid[8-i] == !turn) && win == 0)
			condition = "   GANA J"+std::to_string(!turn+1), win = 1;
	}
	if (win == 1) return false;
	for (int i = 0; i < 9; ++i) if (grid[i] == -1 ) cells++;
	if (cells == 0){
		if (win == 0) condition = "   EMPATE"; return false;
	}
	return true;
}
