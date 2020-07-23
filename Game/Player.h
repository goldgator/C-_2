#pragma once
#include "Actor.h"
#include "Vector2.h"

using namespace nc;

namespace nc {
	class Player : public nc::Actor {
	public:
		virtual eType GetType() { return eType::PLAYER; }


		virtual void Update(float dt) override;
		virtual bool Load(const std::string& filename) override;


	protected:
		float m_thrust = 100;
		nc::Vector2 m_velocity = Vector2(0, 0);
		float m_rotation;
		float m_fireTimer;
		float m_fireRate = 0.3f;
	};
}
