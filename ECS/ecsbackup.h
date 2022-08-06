#pragma once

#ifndef ECS
#define ECS

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;

//Crear entidad
class Entity;

using ComponentID = size_t;

ComponentID getComponentTypeID();

template<typename T> inline ComponentID getComponentTypeID() noexcept{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr size_t maxComponents = 32;

using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component{
public:
	Entity* entity;
	
	virtual void init() {}
	virtual void update() {}
	virtual void draw(){}
	
	virtual ~Component() {}
};

class Entity{
private:
	bool active{true};
	std::vector<std::unique_ptr<Component>> components;
	
	ComponentArray componentArray;
	ComponentBitset componentBitset;
public:
	void update();
	void draw();
	bool isActive() const;
	void destroy();
	
	template<typename T> bool hasComponent() const{
		return componentBitset[getComponentTypeID<T>];
	}
	template<typename T, typename ... TArgs>
	T& addComponent(TArgs&&... mArgs){
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));
		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;
		c->init();
		return *c;
	}
	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
	
};

class Manager{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	
public:
	void update();
	void draw();
	void refresh();
	Entity& addEntity();
};

#endif
