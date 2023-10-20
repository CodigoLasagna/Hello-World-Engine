//nr 1
#include "../../ECS/Components.h"
#include "../../HelloWorldEngine.h"
//Aqui suelo testear cosas nuevas para el motoro
int main(){
	char key{};
	Renderer* main_env = new Renderer(1, 32, 16, 30);
	Manager manager;
	auto& player(manager.addEntity());
	auto& enemy(manager.addEntity());
	const uint32_t walls_max = 1000000;
	Entity* walls[walls_max]{};
	//srand(time(NULL));
	Window* mainwin = new Window(32, 16, 0, 0, false, main_env);
	
	
	for (int i = 0; i < walls_max; i++){
		walls[i] = &manager.addEntity();
		walls[i]->addComponent<PositionComponent>((rand()%30)+1, (rand()%14)+1);
		walls[i]->addComponent<SpriteComponent>("#", mainwin->win);
		walls[i]->getComponent<SpriteComponent>().setColor(rand()%9, -1, false);
	}
	
	player.addComponent<PositionComponent>(1, 1);
	player.addComponent<SpriteComponent>("@", mainwin->win);
	
	enemy.addComponent<PositionComponent>(5, 5);
	enemy.addComponent<SpriteComponent>("O", mainwin->win);
	
	while(key != 'q'){
		main_env->start_renderer();
		mainwin->clean();
		manager.update();
		manager.draw();
		mvwprintw(mainwin->win, 1, 1, "X:%i",player.getComponent<PositionComponent>().x());
		mvwprintw(mainwin->win, 2, 1, "Y:%i",player.getComponent<PositionComponent>().y());
		if (player.getComponent<PositionComponent>().x() >80){
			player.getComponent<PositionComponent>().x(0);
		}
		key = getch();
		
		main_env->update_renderer();
	}
	endwin();
	return 0;
}
