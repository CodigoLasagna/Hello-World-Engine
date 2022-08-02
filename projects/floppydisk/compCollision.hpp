//nr 1
#pragma once
#include "ComponentsFloppy.hpp"

class CollisionComponent : public Component{
private:
	PositionComponent *position;
	SpriteComponent *drawParams;
	PositionComponent *colideObject;
	DrawRectComponent *pipe;
	StatesComponent *state;
public:
	CollisionComponent(){
	}
	
	CollisionComponent(Entity& obj){
		colideObject = &obj.getComponent<PositionComponent>();
		pipe = &obj.getComponent<DrawRectComponent>();
	}
	
	void init() override {
		position = &entity->getComponent<PositionComponent>();
		drawParams = &entity->getComponent<SpriteComponent>();
		state = &entity->getComponent<StatesComponent>();
	}
	
	void update() override{
		if ((position->x()+2 > colideObject->x() && position->x() < colideObject->x()+4) && (position->y() < colideObject->y()-2 || position->y() > colideObject->y()+2)){
			if (state->state() == 0){
				die();
			}
				
			pipe->v(0);
			state->state(1);
		}
		if (position->y() > 22 && state->state() == 0){
			die();
			state->state(1);
		}
	}
	void die(){
		drawParams->setColor(1, -1, false);
		entity->getComponent<GravityComponent>().v(-1.5);
		entity->getComponent<GravityComponent>().g(0.5);
	}
};
