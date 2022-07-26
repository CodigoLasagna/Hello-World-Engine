//nr
#include "../HelloWorldEngine.h"
#include <cstdlib>
#include <ctime>
#include <random>

int main(){
	char key{};
	//Manager manager;
	//auto& player(manager.addEntity());
	//auto& enemy(manager.addEntity());
	//Entity* walls[] = {&manager.addEntity()};
	const uint32_t walls_max =123456789;
	//Entity* walls[walls_max]{};
	srand(time(NULL));
	
	Renderer* mainenv = new Renderer(1, 80, 48, 150);
	Window* mainwin = new Window(80, 48, 0, 0, false, mainenv);
	Instance* walls = new Instance[walls_max]{};
	for (int i = 0; i < walls_max; i++){
		walls[i].m_coordx = (rand()%78)+1;
		walls[i].m_coordy = (rand()%46)+1;
		walls[i].m_fgcolor = rand()%9;
	}
	
	//for (int i = 0; i < walls_max; i++){
	//	walls[i] = &manager.addEntity();
	//	walls[i]->addComponent<PositionComponent>(rand()%80, rand()%80);
	//	walls[i]->addComponent<SpriteComponent>('#', mainwin->win);
	//	walls[i]->getComponent<SpriteComponent>().setColor(rand()%9, -1, false);
	//}
	
	//player.addComponent<PositionComponent>(2, 4);
	//player.addComponent<SpriteComponent>('@', mainwin->win);
	
	//enemy.addComponent<PositionComponent>(5, 5);
	//enemy.addComponent<SpriteComponent>('O', mainwin->win);
	
	while(key != 'q'){
		mainenv->start_renderer();
		mainwin->clean();
		key = getch();
		for (int i = 0; i < walls_max; i++){
			instance_draw(*mainwin, &walls[i]);
			walls[i].m_coordx +=1;
		}
		//manager.update();
		//manager.draw();
		//mvwprintw(mainwin->win, 1, 1, "X:%i",player.getComponent<PositionComponent>().x());
		//mvwprintw(mainwin->win, 2, 1, "Y:%i",player.getComponent<PositionComponent>().y());
		//if (player.getComponent<PositionComponent>().x() >80){
		//	player.getComponent<PositionComponent>().x(0);
		//}
		
		mainenv->update_renderer();
	}
	endwin();
	return 0;
}
