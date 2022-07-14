//nr
#include "../HelloWorldEngine.h"

int main(){
	char key{};
	Renderer* mainenv = new Renderer(1, 60);
	Window* mainwin = new Window(16, 16, 0, 0, false);
	while(key != 'q'){
		mainenv->start_renderer();
		mainwin->clean();
		key = getch();
		mainenv->update_renderer();
	}
	endwin();
	return 0;
}
