//nr
#include <cstdlib>
#include <fstream>
#include "../HelloWorldEngine.h"
#include <random>

int main(){
	srand(time(NULL));
	char key{};
	Renderer* main_env = new Renderer(1, 110);
	int term_w = main_env->get_term_size('w'), term_h = main_env->get_term_size('h');
	int world_w = 28, world_h = 31;
	int xx{0}, yy{0};
	Window* win = new Window[2]{Window(world_w, world_h, -13, 0, false), Window(world_w, 5, world_w-13, -(world_h/2)+2, false)};
	Instance* player = instance_create(int(world_w/2), int(world_h/2)+2, '@');
	Instance* ghost = new Instance[4]{Instance(12, int(world_h/2)-1, 'O'), Instance(13, int(world_h/2)-1, 'O'), Instance(14, int(world_h/2)-1, 'O'), Instance(15, int(world_h/2)-1, 'O')};
	win[1].m_fgcolor = C_BLUE;
	ghost[0].m_fgcolor = C_RED;
	ghost[1].m_fgcolor = C_MAGENTA;
	ghost[2].m_fgcolor = C_CYAN;
	ghost[3].m_fgcolor = C_YELLOW;
	int prev_col[4]{};
	for (int i = 0; i < 4; i++){
		prev_col[i] = ghost[i].m_fgcolor;
		ghost[i].m_bcolor = true;
	}
	int score{};
	int state{};
	int state_counter{};
	
	int tiles = (world_w-2)*(world_h-2);
	Instance* tile = new Instance[tiles]{};
	std::string filename("map.txt");
	std::ifstream indata;
	indata.open(filename);
	while(!indata.is_open()){
		main_env->start_renderer();
		mvwaddstr(win[0].win, world_h/2, 1, "Check if 'map.txt' exists");
		filename = "pacman/map.txt";
		indata.open(filename);
		main_env->update_renderer();
	}
	int count = 0;
	char letter;
	indata >> letter;
	while (letter != '%') {
		if (letter != '$'){
			if (letter == '#'){
				tile[count].set_sprite('#');
				tile[count].m_type = 2;
				tile[count].m_fgcolor = C_BLUE;
			}else if (letter == '.'){
				tile[count].set_sprite('.');
				tile[count].m_type = 1;
				tile[count].m_bcolor = true;
				tile[count].m_fgcolor = C_YELLOW;
			}else if (letter == 'o'){
				tile[count].set_sprite('o');
				tile[count].m_type = 1;
				tile[count].m_bcolor = true;
				tile[count].m_fgcolor = C_YELLOW;
			}else if (letter == ','){
				tile[count].set_sprite(' ');
				tile[count].m_type = 0;
			}else{
				tile[count].set_sprite('#');
				tile[count].m_type = 2;
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

	int sep{world_w-2};
	for (int i = 0; i < tiles; i++){
		if (tile[i].get_sprite() == '#'){
			if ((tile[i+1].get_sprite() == '.' && tile[i-sep].m_type == 1) || (tile[i+1].m_type == 2 && tile[i-sep].m_type == 2)){
				if ((tile[i+sep-1].m_type == 1 || tile[i-sep+1].m_type == 1) && (tile[i+sep].m_type == 1 || tile[i-sep].get_sprite() == ACS_VLINE)){
					tile[i].set_sprite(ACS_LLCORNER);
				}
			}
			if ((tile[i-1].get_sprite() == '.' && tile[i-sep].m_type == 1) || (tile[i-1].m_type == 2 && tile[i-sep].m_type == 2)){
				if ((tile[i+sep+1].m_type == 1 || tile[i-sep+1].m_type == 1) && (tile[i-sep].m_type == 1 || tile[i-sep].get_sprite() == ACS_HLINE || tile[i-sep].get_sprite() == ACS_LLCORNER)){
					if (tile[i-(sep*2)].get_sprite() != 'o')
						tile[i].set_sprite(ACS_ULCORNER);
				}
			}
			if ((tile[i-1].get_sprite() == '.' && tile[i-sep].m_type == 1) || (tile[i-1].m_type == 2 && tile[i-sep].m_type == 2)){
				if ((tile[i+sep+1].m_type == 1 || tile[i-sep-1].m_type == 1) && (tile[i+sep].m_type == 1 || tile[i-sep].get_sprite() == ACS_VLINE)){
					if (tile[i-(sep*2)].get_sprite() != 'o')
						tile[i].set_sprite(ACS_LRCORNER);
				}
			}
			if ((tile[i+1].get_sprite() == '.' && tile[i-sep].m_type == 1) || (tile[i+1].m_type == 2 && tile[i-sep].m_type == 2)){
				if ((tile[i+sep-1].m_type == 1 || tile[i-sep-1].m_type == 1) && (tile[i-sep].m_type == 1 || tile[i-sep].get_sprite() == ACS_HLINE || tile[i-sep].get_sprite() == ACS_LRCORNER)){
					if (tile[i+sep].m_type != 0)
						tile[i].set_sprite(ACS_URCORNER);
				}
			}
			if ((tile[i-1].m_type == 2 || tile[i].m_coordx == 1) && (tile[i+1].get_sprite() == '#' || tile[i+sep].m_type == 0 || tile[i-sep].m_type == 0 || tile[i-(sep*2)].get_sprite() == 'o')){
				if (tile[i-sep].get_sprite() == '.' || tile[i+sep].get_sprite() == '.' || tile[i-sep].get_sprite() == 'o'){
					tile[i].set_sprite(ACS_HLINE);
				}
			}
			if (tile[i-1].m_type == 1 || tile[i+1].m_type == 1){
				if (tile[i+1].m_type == 0 || tile[i-1].m_type == 0 || tile[i].m_coordy == 1){
					tile[i].set_sprite(ACS_VLINE);
				}else if (tile[i-sep].m_type == 2 && tile[i+sep].m_type == 2 || tile[i].m_coordy == 1){
					tile[i].set_sprite(ACS_VLINE);
				}
			}
		}
	}
	
	int spd{0}, temp_spd{1}, wait_spd{1};
	int rand_n{};
	bool wait{};
	char dir{'x'}, temp_dir{'x'}, wait_dir{'x'};
	char lim{}, temp_lim{}, wait_lim{};
	player->m_fgcolor = C_YELLOW;
	player->m_bcolor = true;
	win->m_fgcolor = C_BLUE;
	while (key != 'q') {
		main_env->start_renderer();
		win[0].clean();
		win[1].clean();
		//mvwhline(win[0].win, 10, 10, , 5);
		key = getch();
		temp_dir = dir; temp_spd = spd; temp_lim = lim;
		switch (key) {
			case('w'):
				spd = -1;
				dir = 'y';
				lim = world_h;
				wait = false;
				break;
			case('s'):
				spd = 1;
				dir = 'y';
				lim = world_h;
				wait = false;
				break;
			case('a'):
				spd = -1;
				dir = 'x';
				lim = world_w;
				wait = false;
				break;
			case('d'):
				spd = 1;
				dir = 'x';
				lim = world_w;
				wait = false;
				break;
		}
		wattron(win[0].win, COLOR_PAIR(C_BLUE));
		mvwaddch(win[0].win, 0, 13, ACS_URCORNER);
		mvwaddch(win[0].win, 0, 14, ACS_ULCORNER);
		
		mvwaddch(win[0].win, 9, 0, ACS_LTEE);
		mvwaddch(win[0].win, 13, 0, ACS_BTEE);
		mvwaddch(win[0].win, 9, world_w-1, ACS_RTEE);
		mvwaddch(win[0].win, 13, world_w-1, ACS_BTEE);
		mvwaddch(win[0].win, 15, 0, ACS_TTEE);
		mvwaddch(win[0].win, 19, 0, ACS_LTEE);
		mvwaddch(win[0].win, 15, world_w-1, ACS_TTEE);
		mvwaddch(win[0].win, 14, 0, ' ');
		mvwaddch(win[0].win, 14, world_w-1, ' ');
		mvwaddch(win[0].win, 19, world_w-1, ACS_RTEE);
		
		mvwaddch(win[0].win, 24, 0, ACS_LTEE);
		mvwaddch(win[0].win, 25, 0, ACS_LTEE);
		mvwaddch(win[0].win, 24, world_w-1, ACS_RTEE);
		mvwaddch(win[0].win, 25, world_w-1, ACS_RTEE);
		wattron(win[0].win, COLOR_PAIR(C_BLUE));
		player->set_coord(dir, player->get_coord(dir) + spd);
		for (int i = 0; i < tiles; i++){
			if (tile[i].m_type != -1){
				instance_draw(win[0], &tile[i]);
			}
			if (player->m_coordx == tile[i].m_coordx && (tile[i].m_type >= 2 || tile[i].m_type == 0) && player->m_coordy == tile[i].m_coordy){
				player->set_coord(dir, player->get_coord(dir) - spd);
				wait = true;
				wait_spd = spd; wait_dir = dir; wait_lim = lim;
				spd = temp_spd; dir = temp_dir; lim = temp_lim;
			}
			if (player->m_coordx == tile[i].m_coordx && tile[i].m_type == 1 && player->m_coordy == tile[i].m_coordy){
				tile[i].m_type = -1;
				if (tile[i].get_sprite() == '.'){
					score += 10;
				}else{
					score += 50;
					state = 1;
				}
			}
			if (wait == true){
				if (wait_dir == 'x'){
					if (player->m_coordx+wait_spd == tile[i].m_coordx && player->m_coordy == tile[i].m_coordy && tile[i].m_type != 2){
						spd = wait_spd; dir = wait_dir; lim = wait_lim;
						wait = false;
					}
				}else if (wait_dir == 'y'){
					if (player->m_coordx == tile[i].m_coordx && player->m_coordy+wait_spd == tile[i].m_coordy && tile[i].m_type != 2){
						spd = wait_spd; dir = wait_dir; lim = wait_lim;
						wait = false;
					}
				}
			}
			
			for (int j = 0; j < 4; j++){
				rand_n = rand()%4;
				if (ghost[j].m_coordx+1 == tile[i].m_coordx && ghost[j].m_coordy == tile[i].m_coordy && tile[i].m_type == 2 && ghost[j].m_type == 0){
					while(rand_n == ghost[j].m_type){
						rand_n = rand()%4;
					}
					ghost[j].m_type = rand_n;
				}
				if (ghost[j].m_coordx-1 == tile[i].m_coordx && ghost[j].m_coordy == tile[i].m_coordy && tile[i].m_type == 2 && ghost[j].m_type == 1){
					while(rand_n == ghost[j].m_type){
						rand_n = rand()%4;
					}
					ghost[j].m_type = rand_n;
				}
				if (ghost[j].m_coordx == tile[i].m_coordx && ghost[j].m_coordy+1 == tile[i].m_coordy && tile[i].m_type == 2 && ghost[j].m_type == 2){
					while(rand_n == ghost[j].m_type){
						rand_n = rand()%4;
					}
					ghost[j].m_type = rand_n;
				}
				if (ghost[j].m_coordx == tile[i].m_coordx && ghost[j].m_coordy-1 == tile[i].m_coordy && tile[i].m_type == 2 && ghost[j].m_type == 3){
					while(rand_n == ghost[j].m_type){
						rand_n = rand()%4;
					}
					ghost[j].m_type = rand_n;
				}
		}
			}
		for (int i = 0; i < 4; i++){
			switch (ghost[i].m_type) {
				case(0):
					rand_n = rand()%4;
					if (ghost[i].m_coordx < world_w-2){
						ghost[i].m_coordx += 1;
					}else{
						while(rand_n == ghost[i].m_type){
							rand_n = rand()%4;
						}
						ghost[i].m_type = rand_n;
					}
					break;
				case(1):
					rand_n = rand()%4;
					if (ghost[i].m_coordx > 1){
						ghost[i].m_coordx -= 1;
					}else{
						while(rand_n == ghost[i].m_type){
							rand_n = rand()%4;
						}
						ghost[i].m_type = rand_n;
					}
					break;
				case(2):
					rand_n = rand()%4;
					if (ghost[i].m_coordy < world_h-2){
						ghost[i].m_coordy += 1;
					}else{
						while(rand_n == ghost[i].m_type){
							rand_n = rand()%4;
						}
						ghost[i].m_type = rand_n;
					}
					break;
				case(3):
					rand_n = rand()%4;
					if (ghost[i].m_coordy > 1){
						ghost[i].m_coordy -= 1;
					}else{
						while(rand_n == ghost[i].m_type){
							rand_n = rand()%4;
						}
						ghost[i].m_type = rand_n;
					}
					break;
			}
			if (ghost[i].m_coordx > world_w){
				ghost[i].m_coordx = 0;
			}
		}
		
		wattron(win[1].win, A_BOLD | COLOR_PAIR(C_YELLOW));
		mvwprintw(win[1].win, 2, (world_w/2)-5, "Score: %i", score);
		wattroff(win[1].win, A_BOLD | COLOR_PAIR(C_YELLOW));
		if (state == 1 && state_counter < 40){
			state_counter+=1;
		}else if (state == 1 && state_counter == 40){
			state = 0;
		}else if (state == 0 && state_counter > 0 ){
			state_counter--;
		}
		if (state_counter < 14 && state_counter > 0){
			if (state_counter % 2){
				win[0].m_bcolor = !win[0].m_bcolor;
				win[1].m_bcolor = !win[1].m_bcolor;
				for (int i = 0; i < 4; i++){
					if (ghost[i].m_fgcolor != C_BLUE){
						prev_col[i] = ghost[i].m_fgcolor;
						ghost[i].m_fgcolor = C_BLUE;
					}else{
						ghost[i].m_fgcolor = prev_col[i];
					}
				}
				for (int i = 0; i < tiles; i++){
					if (tile[i].m_type == 2){
						tile[i].m_bcolor = !tile[i].m_bcolor;
					}
				}
			}else{
			}
		}
		if (((player->get_coord(dir)-1 < 0) || (player->get_coord(dir)+1 > lim-1)) && player->m_coordy != 14){
			player->set_coord(dir, player->get_coord(dir) - spd);
		}
		if (player->m_coordx >= world_w || player->m_coordx <= -1)
			player->m_coordx -= (world_w)*(spd);
		instance_draw(win[0], player);
		for (int i = 0; i < 4; i++){
			instance_draw(win[0], &ghost[i]);
		}
		main_env->update_renderer();
	}
	endwin();
	return 0;
}
