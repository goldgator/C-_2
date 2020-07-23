#include "Player.h"
#include "Transform.h"
#include "MathExt.h"
#include "Vector2.h"
#include "projectile.h"
#include "Scene.h"
#include "ParticleSystem.h"

using namespace nc;

namespace nc {

	bool Player::Load(const std::string& filename)
	{
		bool success = false;
		std::ifstream stream(filename);

		if (stream.is_open())
		{
			success = true;
			Actor::Load(stream);

			stream >> m_thrust;
			stream >> m_rotation;


			stream.close();
		}
		return success;
	}

	void Player::Update(float dt)
	{

		m_fireTimer += dt;

		if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
		{
			m_fireTimer = 0;
			//add enemy to scene
			Projectile* projectile = new Projectile;
			projectile->Load("projectile.txt");
			projectile->GetTransform().position = m_transform.position;
			projectile->GetTransform().angle = m_transform.angle;
			projectile->GetTransform().scale = 1.5;
			m_scene->AddActor(projectile);
		}

		//position
		nc::Vector2 force;
		if (Core::Input::IsPressed('W')) { force = nc::Vector2(1,0) * m_thrust; }
		force = nc::Vector2::Rotate(force, m_transform.angle);

		//force = force + nc::Vector2{ 0,100 };

		m_velocity = m_velocity + (force * dt);
		m_velocity = m_velocity * 0.98f;

		m_transform.position += m_velocity * dt;

		//rotate
		if (Core::Input::IsPressed('A')) { m_transform.angle -= nc::DegreesToRadians(m_rotation) * dt; }
		if (Core::Input::IsPressed('D')) { m_transform.angle += nc::DegreesToRadians(m_rotation) * dt; }

		m_transform.position = nc::clamp(m_transform.position, { 0,0 }, { 800,600 });

		if (force.LengthSqr() > 0)
		{
			particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 20, 1, nc::Color(0,255,0), 1, 100, 200);
		}

		m_transform.Update();

	}

}
