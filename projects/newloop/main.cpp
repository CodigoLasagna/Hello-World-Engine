//nr 1
#include "../../HelloWorldEngine.h"
void update();//se crea el ciclo de actualizaciones logicas
void draw();//se crea el ciclo de actualizaciones de dibujo
void input();//se crea el ciclo de actualizaciones de teclas o entrada(aún no implementado(

auto* main_env = new Renderer(1, 64, 32, 12.0, 'q');//se crea el motor, correra a 12 ciclos por segundo
													//se le asigna la tecla Q como tecla de salida
Window main_win = Window(64, 32, 0, 0, false, main_env);//se crea una ventana
auto player = instance_create(1, 8, '@');//se crea un objeto

int main(){//programa inicial
	main_env->game_loop(update, draw);//se mandan los ciclos a usar
	return 0;
}

void update(){//aqui se actualiza toda la logica del programa
	player->m_coordx+= 1;
}

void draw(){//aqui se actualiza todo lo que se tenga que dibujar
	main_win.clean();
	instance_draw(main_win, player);
}
