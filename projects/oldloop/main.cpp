//nr 1
#include "../../HelloWorldEngine.h"
auto* main_env = new Renderer(1, 64, 16, 120.0);//se crea el motor de tipo 1 con dimensiones 64x16
												// y 120 milisegundos entre fotogramas (no es preciso)
Window main_win = Window(16, 8, 0, 0, false, main_env);//se crea una ventana en el motor
auto player = instance_create(2, 2, '@');//se crea un objeto
int key{};//se inicia la variable para botones

int main(){
	while (key != 'q') {//mientras no se presione Q el juego sigue
		main_env->start_renderer();//inicio de ciclo de juego
		instance_draw(main_win, player);//se dibuja una entidad
		player->m_coordx+=1;//se actualiza el jugador
		key = getch();//se espera a que se presione una tecla
		main_env->update_renderer();//se finaliza el ciclo del juego
	}
	endwin();//se limpian rastros del motor
	return 0;//se sale del programa
}

