//nr 1
#include "../../HelloWorldEngine.h"
void update();
void draw();
void input();

auto* main_env = new Renderer(1, 64, 32, 12.0, 'q');
auto main_win = Window(64, 32, 0, 0, 0, main_env);
auto player = instance_create(1, 16, '@');

int main(){
	main_env->game_loop(update, draw);
	return 0;
}

void update(){
	player->m_coordx+= 1;
}

void draw(){
	main_win.clean();
	instance_draw(main_win, player);
}
