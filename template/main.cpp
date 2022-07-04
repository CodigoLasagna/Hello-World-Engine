#include  "HelloWorldEngine.h" 
#include <random>

int main(){
	Renderer* main_env = new Renderer(1, 75);
	double term_w = main_env->get_term_size('w'), term_h = main_env->get_term_size('h');
	int world_w = term_w, world_h = term_h-3;
	Window* win = new Window[2]{Window(30, 20), Window(5, 5, 2, 2, 1)};
	
	Instance* head = instance_create(10, 10, '@');
	
	char key{};
	while (key != 'q') {
		main_env->start_renderer();
		
		key = getch();
		main_env->update_renderer();
	}
	
	endwin();
	return 0;
}
