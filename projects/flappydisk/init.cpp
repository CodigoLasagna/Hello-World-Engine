//nr 1
#pragma once
#include "../../HelloWorldEngine.h"
#include "ComponentsFloppy.hpp"
Manager manager;

auto* main_env = new Renderer(1, 32, 25, 12.0, 'q');
auto main_win = Window(32, 25, 0, 0, false, main_env);
auto& floppy(manager.addEntity());
auto& pipes(manager.addEntity());
auto& score(manager.addEntity());
int key{};

void init(){
	score.addComponent<StatesComponent>();
	score.addComponent<TextComponent>(main_win.win, ":>");
	
	floppy.addComponent<PositionComponent>(8, 1);
	floppy.addComponent<GravityComponent>(0.1, 5.0, 1);
	floppy.addComponent<SpriteComponent>("\uf748", main_win.win);
	floppy.getComponent<SpriteComponent>().setColor(3, -1, true);
	floppy.addComponent<StatesComponent>();
	
	pipes.addComponent<PositionComponent>(33, 12);
	pipes.addComponent<DrawRectComponent>(4, 17, main_win.win);
	pipes.getComponent<DrawRectComponent>().setColor(2, -1, true);
	
	floppy.addComponent<CollisionComponent>(pipes);
	//pipes.addComponent<SpriteComponent>("@", main_win.win);//remove later
}
