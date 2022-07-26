#pragma once

#ifndef COMP_POS
#define COMP_POS

#include "Components.h"
class PositionComponent : public Component{
private:
	int xpos{}, ypos{};
public:
	PositionComponent(){
		xpos = 0;
		ypos = 0;
	}
	PositionComponent(int x, int y){
		xpos = x;
		ypos = y;
	}
	
	// void init() override{
	// 	xpos = 0; ypos = 0;
	// }
	void update() override{
		xpos++;
		//ypos;
	}
	// void setPos(int x, int y){
	// 	xpos = x; ypos = y;
	// }
	int x() { return xpos; }
	int y() { return ypos; }
	void x(int x) { xpos = x; }
	void y(int y) { ypos = y; }
};
#endif
