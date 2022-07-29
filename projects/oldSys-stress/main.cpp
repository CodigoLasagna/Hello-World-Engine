//nr 1
#include "../../HelloWorldEngine.h"

int main(){
	char key{};
	const uint32_t walls_max = 123456789;
	srand(time(NULL));
	
	Renderer* mainenv = new Renderer(1, 80, 48, 150);
	Window* mainwin = new Window(80, 48, 0, 0, false, mainenv);
	Instance* walls = new Instance[walls_max]{};
	for (int i = 0; i < walls_max; i++){
		walls[i].m_coordx = (rand()%78)+1;
		walls[i].m_coordy = (rand()%46)+1;
		walls[i].m_fgcolor = rand()%9;
	}
	
	while(key != 'q'){
		mainenv->start_renderer();
		mainwin->clean();
		key = getch();
		for (int i = 0; i < walls_max; i++){
			instance_draw(*mainwin, &walls[i]);
			walls[i].m_coordx +=1;
		}
		mainenv->update_renderer();
	}
	endwin();
	return 0;
}
