//nr 1
#include <iostream>
#include <ctime>
int main(){
	clock_t previous = clock();
	double lag{};
	while (true){
		clock_t current = clock();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;
		//input here
		while (lag > 100){
			//update here
			std::cout << elapsed << "\n";
			lag -= 100;
		}
		//render here
	}
}
