//nr 1
#pragma once
#include "ComponentsFloppy.hpp"

class GravityComponent : public Component{
private:
	PositionComponent *position;
	float m_g{}, m_m{}, m_v{};
public:
	GravityComponent(){
		m_g = 0;
		m_m = 5;
		m_v = 0;
	}
	GravityComponent(float g, float m, float v){
		m_g = g; m_m = m; m_v = v;
	}
	void init() override {
		position = &entity->getComponent<PositionComponent>();
	}
	
	void update() override{
		if (m_v < 2)
			m_v += m_g;
		if (m_v > -0.0 && m_v < 0.2)
			m_v = 1;
		if (m_v > 1.5 && m_v < 2)
			m_v = 2;
		position->y(position->y()+m_v);
	}
	void v(float v) { m_v = v; }
	void g(float g) { m_g = g; }
	void m(float m) { m_m = m; }
	float v() { return m_v; }
	float g() { return m_g; }
	float m() { return m_m; }
};
