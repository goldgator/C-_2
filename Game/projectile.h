#pragma once
#include "Actor.h"
#include "Vector2.h"


using namespace nc;


class Projectile : public nc::Actor {
public:

	virtual eType GetType() { return eType::PROJECTILE; }

	virtual void OnCollision(Actor* actor);

	virtual void Update(float dt);

	virtual void Draw(Core::Graphics& graphics);

	virtual bool Load(const std::string& filename);

	void SetThrust(float thrust) { m_thrust = thrust; }

	void SetTarget(Actor* actor) { m_target = actor; }



protected:
	float m_thrust = 100;
	Vector2 velocity = Vector2( 0, 0 );
	Actor* m_target;

};