//nr
#include "../HelloWorldEngine.h"

int main(){
	char key{};
	Renderer* mainenv = new Renderer(1, 40, 30, 60);
	Window* mainwin = new Window(16, 16, 0, 0, false, mainenv);
	int test = mainwin->mainRender->m_min_height;
	int numb{};
	while(key != 'q'){
		mainenv->start_renderer();
		mainwin->clean();
		key = getch();
		mainenv->update_renderer();
	}
	endwin();
	return 0;
}
