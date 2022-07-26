//nr
#include "../HelloWorldEngine.h"

Manager manager;
auto& player(manager.addEntity());

int main(){
	char key{};
	
	Renderer* mainenv = new Renderer(1, 80, 80, 60);
	Window* mainwin = new Window(80, 48, 0, 0, false, mainenv);
	
	player.addComponent<PositionComponent>(2, 2);
	player.addComponent<SpriteComponent>('@', mainwin->win);
	player.getComponent<SpriteComponent>();
	
	while(key != 'q'){
		mainenv->start_renderer();
		mainwin->clean();
		manager.update();
		manager.draw();
		mvwprintw(mainwin->win, 1, 1, "X:%i",player.getComponent<PositionComponent>().x());
		mvwprintw(mainwin->win, 2, 1, "Y:%i",player.getComponent<PositionComponent>().y());
		
		key = getch();
		mainenv->update_renderer();
	}
	endwin();
	return 0;
}
