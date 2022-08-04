//nr 1
#include "../../ECS/Components.h"
#include "../../ECS/Components.h"
#include "../../HelloWorldEngine.h"
//crear objetos
void init();
//loop de actualización
void update();
//loop de dibujo
void draw();

auto main_env = Renderer(1, 32, 16, 24.0, 'q');
auto main_win = Window(32, 16, 0, 0, false, &main_env);
Manager manager;
auto& player(manager.addEntity());

int main(){
	init();
	main_env.game_loop(update, draw);
}

void update(){
	player.update();
}
void draw(){
	main_win.clean();
	player.draw();
}

void init(){
	player.addComponent<PositionComponent>(2, 1);
	player.addComponent<SpriteComponent>("#", main_win.win);
}
