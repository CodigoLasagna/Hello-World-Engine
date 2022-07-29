//nr 1
#include "../../HelloWorldEngine.h"

int main(){
	int key{};
	auto* main_env = new Renderer(1, 32, 16, 120);
	Window* mainwin = new Window(32, 16, 0, 0, 0, main_env);
	auto player = instance_create(5, 5, "\uf17c", 1);
	
	while(key != int('q')){
		main_env->start_renderer();
		mainwin->clean();
		instance_draw(*mainwin, player);
		
		//mvwaddchw(mainwin->win, 10, 10, 'ñ'); //to take in count
		mvwprintw(mainwin->win, 10, 10, "\u2663");
		mvwprintw(mainwin->win, 10, 10, "\uf17c");
		mvwaddstr(mainwin->win, 20, 10, "ñ");
		
		key = getch();
		
		main_env->update_renderer();
	}
	endwin();
	return 0;
}
