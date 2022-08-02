//nr 1
#pragma once
#include "ComponentsFloppy.hpp"
#include "init.cpp"

void update(){
	score.getComponent<TextComponent>().changeText(std::to_string(score.getComponent<StatesComponent>().state()).c_str());
	pipes.update();
	floppy.update();
	if (main_env->m_key == ' ' || main_env->m_key == 'u' || main_env->m_key == 'w'){
		if (floppy.getComponent<StatesComponent>().state() == 0)
			floppy.getComponent<GravityComponent>().v(-0.5);
	}
	if (main_env->m_key == 'r'){
		score.getComponent<StatesComponent>().state(0);
		pipes.getComponent<PositionComponent>().x(-3);
		pipes.getComponent<DrawRectComponent>().v(1);
		floppy.getComponent<StatesComponent>().state(0);
		floppy.getComponent<GravityComponent>().g(0.1);
		floppy.getComponent<GravityComponent>().m(5.0);
		floppy.getComponent<GravityComponent>().v(-0.2);
		floppy.getComponent<PositionComponent>().y(8);
		floppy.getComponent<SpriteComponent>().setColor(3, -1, true);
	}
	if (floppy.getComponent<PositionComponent>().x() == pipes.getComponent<PositionComponent>().x()){
		score.getComponent<StatesComponent>().state(score.getComponent<StatesComponent>().state()+1);
	}
	if (floppy.getComponent<StatesComponent>().state() == 1){
		score.getComponent<TextComponent>().changeText("Press R to restart.");
	}
}
void draw(){
	main_win.clean();
	pipes.draw();
	score.draw();
	floppy.draw();
}
