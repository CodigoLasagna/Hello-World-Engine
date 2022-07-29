//nr 1
#include "../../HelloWorldEngine.h"
#include <random>

void inputs();
void restart();
void rand_p();

Renderer* main_env = new Renderer(1, 64, 38, 65);
int world_w{}, world_h{};
char key{};
char coord{'x'};
int spd{1};
int score{};
int b_score{};
bool collision{};

Instance* head = instance_create(0, 0, '@');
Instance* pellet = instance_create(0, 0, '*');

int main(){
	double term_w = main_env->get_term_size('w'), term_h = main_env->get_term_size('h');
	int menu_w = 22, menu_h = 11;
	Window* errorM = new Window(term_w, term_h, 0, 0, 0, main_env);
	world_w = 60, world_h = 33;
	errorM->show(false);
	int total_b = world_w*world_h;
	srand(time(NULL));
	int prev_x[total_b], prev_y[total_b];
	Instance* body = new Instance[total_b]{*instance_create(1, 1, '#')};
	head->m_coordx = int(world_w/2), head->m_coordy = int(world_h/2);
	rand_p();
	Window* win = new Window[3]{
		Window(world_w, world_h, 0, 1, 0, main_env),
		Window(world_w, 3, 0, -(world_h/2)-1, 0, main_env),
		Window(menu_w, menu_h, 0, 0, 0, main_env)
	};
	
	instance_draw(win[0], head);
	instance_draw(win[0], pellet);
	while (key != 'q') {
		main_env->start_renderer();
		win[0].clean();
		win[1].clean();
		
		inputs();
		
		prev_x[0] = head->m_coordx; prev_y[0] = head->m_coordy;
		if (collision != true)
			head->set_coord(coord, head->get_coord(coord)+(1*spd));
		if (head->m_coordx >= world_w-1 || head->m_coordx <= 0)
			head->m_coordx -= (world_w-2)*(spd);
		if (head->m_coordy >= world_h-1 || head->m_coordy <= 0)
			head->m_coordy -= (world_h-2)*(spd); 
		if ((head->m_coordx == pellet->m_coordx) && (head->m_coordy == pellet->m_coordy)){
			rand_p();
			++score;
		}
		if ((body->m_coordx == pellet->m_coordx) && (body->m_coordy == pellet->m_coordy)){
			rand_p();
		}
		
		instance_draw(win[0], pellet);
		instance_draw(win[0], head);
		for (int i = 1; i <= score; i ++){
			prev_y[i] = body[i].m_coordy; prev_x[i] = body[i].m_coordx;
			body[i].m_coordy = prev_y[i-1]; body[i].m_coordx = prev_x[i-1];
			instance_draw(win[0], &body[i]);
			if (head->m_coordx == body[i].m_coordx && head->m_coordy == body[i].m_coordy){ collision = true; }
		}
		
		mvwprintw(win[1].win, 1, (world_w/2)-5, "Score: %i", score);
		if (collision == true){
			win[2].clean();
			if (score > b_score)
				b_score = score;
			mvwprintw(win[1].win, 1, (world_w/2)-7,"[GAME - OVER]");
			mvwprintw(win[2].win, 1, (menu_w/2)-6,"[HIGH SCORE]");
			mvwprintw(win[2].win, 2, (menu_w/2)-1,"%i", b_score);
			mvwprintw(win[2].win, 3, (menu_w/2)-6,"[THIS  GAME]");
			mvwprintw(win[2].win, 4, (menu_w/2)-1,"%i", score);
		}
		win[2].show(collision);
		main_env->update_renderer();
	}
	restart();
	
	endwin();
	instance_destroy(head);
	delete [] body;
	return 0;
}

void inputs(){
	key = getch();
	switch (key) {
		case('w'):
			if (coord == 'x'){
				spd = -1;
				coord = 'y';
			}
		break;
		case('s'):
			if (coord == 'x'){
				spd = 1;
				coord = 'y';
			}
		break;
		case('a'):
			if (coord == 'y'){
				spd = -1;
				coord = 'x';
			}
		break;
		case('d'):
			if (coord == 'y'){
				spd = 1;
				coord = 'x';
			}
		break;
		case('r'):
			restart();
		break;
	}
}
void rand_p(){
	pellet->m_coordx = 1+(rand()%((int)world_w-2));
	pellet->m_coordy = 1+(rand()%((int)world_h-2));
}

void restart(){
	score = 0;
	head->m_coordx = int(world_w/2); head->m_coordy = int(world_h/2);
	rand_p();
	collision = false;
}
