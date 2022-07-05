//nr
#include "../HelloWorldEngine.h"

int main(){
	char key{};
	Renderer* main_env = new Renderer(1, 65);
	int term_w = main_env->get_term_size('w'), term_h = main_env->get_term_size('h');
	// Window* win = new Window[1]{Window(70, 50, 0, 0, false)};
	Window* win = new Window[1]{Window(term_w, term_h, 0, 0, false)};
	Instance* player = instance_create(4, 4, '@');
	player->m_fgcolor = C_MAGENTA;
	win->m_fgcolor = C_MAGENTA;
	while (key != 'q') {
		main_env->start_renderer();
		win[0].clean();
		instance_draw(win[0].win, player);
		key = getch();
		main_env->update_renderer();
	}
	endwin();
	return 0;
}
