//nr 1
#include "gameloop.cpp"

int main(){
	init();
	main_env->game_loop(update, draw);
}
