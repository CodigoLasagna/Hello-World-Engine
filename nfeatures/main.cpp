//nr
#include "../HelloWorldEngine.h"

int main(){
	char key{};
	Renderer* mainenv = new Renderer(1, 16, 16, 60);
	Window* mainwin = new Window(16, 8, 0, -4, false, mainenv);
	Window* second_w = new Window(16, 8, 0, 4, false, mainenv);
	int test = mainwin->mainRender->m_min_height;
	int numb{};
	while(key != 'q'){
		mainenv->start_renderer();
		mainwin->clean();
		second_w->clean();
		key = getch();
		mainenv->update_renderer();
	}
	endwin();
	return 0;
}
