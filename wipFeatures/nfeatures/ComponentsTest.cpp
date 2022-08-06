#include "ComponentsTest.h"

TestComponent::TestComponent(){
	xpos = 0;
	ypos = 0;
}

TestComponent::TestComponent(int x, int y){
	xpos = x;
	ypos = y;
}

void TestComponent::update(){
	xpos;
	ypos;
}

int TestComponent::x() { return xpos; }
int TestComponent::y() { return ypos; }
void TestComponent::x(int x) { xpos = x; }
void TestComponent::y(int y) { ypos = y; }
