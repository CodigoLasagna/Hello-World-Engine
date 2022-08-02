//nr 1
#pragma once
#include "ComponentsFloppy.hpp"

class StatesComponent : public Component{
private:
	float m_state{};
public:
	StatesComponent(){
		m_state = 0;
	}
	void init() override {
	}
	
	void update() override{
	}

	int state() {return m_state; }
	void state(int state) {m_state = state;}
};
