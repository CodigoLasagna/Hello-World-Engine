#pragma once
#include "../../ECS/ecs.h"
#include "ComponentsTest.h"

class TestComponent : public Component{
private:
	int xpos{}, ypos{};
public:
	TestComponent();
	
	TestComponent(int x, int y);
	
	void update() override;
	
	int x();
	int y();
	void x(int x);
	void y(int y);
};
