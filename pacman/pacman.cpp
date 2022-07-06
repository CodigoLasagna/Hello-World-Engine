//nr
#include "../HelloWorldEngine.h"
#include <curses.h>
#include <fstream>

int main(){
	char key{};
	Renderer* main_env = new Renderer(1, 110);
	int term_w = main_env->get_term_size('w'), term_h = main_env->get_term_size('h');
	int world_w = 28, world_h = 31;
	int xx{0}, yy{0};
	Window* win = new Window[1]{Window(world_w, world_h, 0, 0, false)};
	Instance* player = instance_create(int(world_w/2)-1, int(world_h/2)+2, '@');
	Instance* ghost = new Instance[4]{Instance(12, int(world_h/2)-2, 'O'), Instance(13, int(world_h/2)-2, 'O'), Instance(14, int(world_h/2)-2, 'O'), Instance(15, int(world_h/2)-2, 'O')};
	ghost[0].m_fgcolor = C_RED;
	ghost[1].m_fgcolor = C_MAGENTA;
	ghost[2].m_fgcolor = C_CYAN;
	ghost[3].m_fgcolor = C_YELLOW;
	
	int tiles = (world_w-2)*(world_h-2);
	Instance* tile = new Instance[tiles]{};
	std::string filename("map.txt");
	std::ifstream indata;
	indata.open(filename);
	int count = 0;
	char letter;
	indata >> letter;
	while (letter != '%') {
		if (letter != '$'){
			if (letter == '#'){
				tile[count].set_sprite('#');
				tile[count].m_type = 1;
				tile[count].m_fgcolor = C_BLUE;
			}else if( letter == 'u'){
				tile[count].set_sprite('-');
				tile[count].m_type = 1;
				tile[count].m_fgcolor = C_BLUE;
			}else if( letter == 'v'){
				tile[count].set_sprite('|');
				tile[count].m_type = 1;
				tile[count].m_fgcolor = C_BLUE;
			}else if( letter == 'r'){
				tile[count].set_sprite('r');
				tile[count].m_type = 1;
				tile[count].m_fgcolor = C_BLUE;
			}else if( letter == 'l'){
				tile[count].set_sprite('l');
				tile[count].m_type = 1;
				tile[count].m_fgcolor = C_BLUE;
			}else if( letter == 'R'){
				tile[count].set_sprite('R');
				tile[count].m_type = 1;
				tile[count].m_fgcolor = C_BLUE;
			}else if( letter == 'L'){
				tile[count].set_sprite('L');
				tile[count].m_type = 1;
				tile[count].m_fgcolor = C_BLUE;
			}else if (letter == '.'){
				tile[count].set_sprite('.');
				tile[count].m_type = 2;
				tile[count].m_bcolor = true;
				tile[count].m_fgcolor = C_YELLOW;
			}else if (letter == 'o'){
				tile[count].set_sprite('o');
				tile[count].m_type = 2;
				tile[count].m_bcolor = true;
				tile[count].m_fgcolor = C_YELLOW;
			}else if (letter == ','){
				tile[count].set_sprite(' ');
				tile[count].m_type = 0;
			}else{
				tile[count].set_sprite(' ');
				tile[count].m_type = 3;
			}
			tile[count].m_coordx = xx+1;
			tile[count].m_coordy = yy+1;
			count++;
			xx++;
		}else{
			yy++;
			xx = 0;
		}
		indata >> letter;
	}
	
	int spd{1}, temp_spd{1};
	char dir{'x'}, temp_dir{'x'};
	char lim{}, temp_lim{};
	player->m_fgcolor = C_YELLOW;
	player->m_bcolor = true;
	win->m_fgcolor = C_BLUE;
	while (key != 'q') {
		main_env->start_renderer();
		win[0].clean();
		//mvwhline(win[0].win, 10, 10, , 5);
		key = getch();
		temp_dir = dir; temp_spd = spd; temp_lim = lim;
		switch (key) {
			case('w'):
				spd = -1;
				dir = 'y';
				lim = world_h;
				break;
			case('s'):
				spd = 1;
				dir = 'y';
				lim = world_h;
				break;
			case('a'):
				spd = -1;
				dir = 'x';
				lim = world_w;
				break;
			case('d'):
				spd = 1;
				dir = 'x';
				lim = world_w;
				break;
		}
		wattron(win[0].win, COLOR_PAIR(C_BLUE));
		mvwaddch(win[0].win, 0, 13, ACS_URCORNER);
		mvwaddch(win[0].win, 0, 14, ACS_ULCORNER);
		
		mvwaddch(win[0].win, 9, 0, ACS_LTEE);
		mvwaddch(win[0].win, 13, 0, ACS_LTEE);
		mvwaddch(win[0].win, 9, world_w-1, ACS_RTEE);
		mvwaddch(win[0].win, 13, world_w-1, ACS_RTEE);
		mvwaddch(win[0].win, 15, 0, ACS_LTEE);
		mvwaddch(win[0].win, 19, 0, ACS_LTEE);
		mvwaddch(win[0].win, 15, world_w-1, ACS_RTEE);
		mvwaddch(win[0].win, 19, world_w-1, ACS_RTEE);
		
		mvwaddch(win[0].win, 24, 0, ACS_LTEE);
		mvwaddch(win[0].win, 25, 0, ACS_LTEE);
		mvwaddch(win[0].win, 24, world_w-1, ACS_RTEE);
		mvwaddch(win[0].win, 25, world_w-1, ACS_RTEE);
		wattron(win[0].win, COLOR_PAIR(C_BLUE));
		player->set_coord(dir, player->get_coord(dir) + spd);
		for (int i = 0; i < tiles; i++){
			instance_draw(win[0].win, &tile[i]);
			wattron(win[0].win, COLOR_PAIR(C_BLUE));
			if (tile[i].get_sprite() == '-'){
				mvwaddch(win[0].win, tile[i].m_coordy, tile[i].m_coordx, ACS_HLINE);
			}else if (tile[i].get_sprite() == '|'){
				mvwaddch(win[0].win, tile[i].m_coordy, tile[i].m_coordx, ACS_VLINE);
			}else if (tile[i].get_sprite() == 'r'){
				mvwaddch(win[0].win, tile[i].m_coordy, tile[i].m_coordx, ACS_ULCORNER);
			}else if (tile[i].get_sprite() == 'l'){
				mvwaddch(win[0].win, tile[i].m_coordy, tile[i].m_coordx, ACS_URCORNER);
			}else if (tile[i].get_sprite() == 'R'){
				mvwaddch(win[0].win, tile[i].m_coordy, tile[i].m_coordx, ACS_LLCORNER);
			}else if (tile[i].get_sprite() == 'L'){
				mvwaddch(win[0].win, tile[i].m_coordy, tile[i].m_coordx, ACS_LRCORNER);
			}
			wattroff(win[0].win, COLOR_PAIR(C_BLUE));
			if (player->m_coordx == tile[i].m_coordx && (tile[i].m_type == 1 || tile[i].m_type == 0) && player->m_coordy == tile[i].m_coordy){
				player->set_coord(dir, player->get_coord(dir) - spd);
				spd = temp_spd; dir = temp_dir; lim = temp_lim;
			}
			if (player->m_coordx == tile[i].m_coordx && tile[i].m_type == 2 && player->m_coordy == tile[i].m_coordy){
				tile[i].m_coordx = -1;
			}
		}
		if (((player->get_coord(dir)-1 < 0) || (player->get_coord(dir)+1 > lim-1)) && player->m_coordy != 14){
			player->set_coord(dir, player->get_coord(dir) - spd);
		}
		if (player->m_coordx >= world_w || player->m_coordx <= -1)
			player->m_coordx -= (world_w)*(spd);
		mvwaddch(win[0].win, 12, 13, ACS_HLINE);
		mvwaddch(win[0].win, 12, 14, ACS_HLINE);
		instance_draw(win[0].win, player);
		for (int i = 0; i < 4; i++){
			instance_draw(win[0].win, &ghost[i]);
		}
		main_env->update_renderer();
	}
	endwin();
	return 0;
}
