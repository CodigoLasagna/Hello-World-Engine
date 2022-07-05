//nr
#include "../HelloWorldEngine.h"

int main(){
	char key{};
	Renderer* main_env = new Renderer(1, 65);
	int term_w = main_env->get_term_size('w'), term_h = main_env->get_term_size('h');
	int world_w = 50, world_h = 30;
	Window* win = new Window[1]{Window(world_w, world_h, 0, 0, false)};
	Instance* player = instance_create(int(world_w/2), int(world_h/2), '@');
	Instance* ghost = new Instance[4]{Instance(4, 4, '%'), Instance(5, 4, '%'), Instance(6, 4, '%'), Instance(7, 4, '%')};
	int walls = 60;
	Instance* wall = new Instance[walls]{};
	ghost[0].m_fgcolor = C_RED;
	ghost[1].m_fgcolor = C_MAGENTA;
	ghost[2].m_fgcolor = C_CYAN;
	ghost[3].m_fgcolor = C_YELLOW;

	int spd{1};
	char dir{'y'};
	char lim{};
	player->m_fgcolor = C_YELLOW;
	player->m_bcolor = true;
	win->m_fgcolor = C_BLUE;
	while (key != 'q') {
		main_env->start_renderer();
		win[0].clean();
		//mvwhline(win[0].win, 10, 10, , 5);
		key = getch();
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
		player->set_coord(dir, player->get_coord(dir) + spd);
		if ((player->get_coord(dir)-1 < 0) || (player->get_coord(dir)+1 > lim-1)){
			player->set_coord(dir, player->get_coord(dir) - spd);
		}
		instance_draw(win[0].win, player);
		for (int i = 0; i < 4; i++){
			instance_draw(win[0].win, &ghost[i]);
		}
		for (int i = 0; i < walls; i++){
			instance_draw(win[0].win, &wall[i]);
			wall[i].m_coordx = i;
		}
		main_env->update_renderer();
	}
	endwin();
	return 0;
}
