#include "Enemy.h"
#include "MathExt.h"
#include "Scene.h"
#include "ParticleSystem.h"

using namespace nc;

void Enemy::Update(float dt)
{


	nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
	m_transform.angle = std::atan2(direction.y, direction.x);
	nc::Vector2 velocity = direction.Normalized() * 0;
	direction.Normalize();
	velocity = direction * m_thrust;
	m_transform.position += velocity * dt;


	m_transform.Update();
}

void Enemy::Draw(Core::Graphics& graphics)
{
	m_shape.Draw(graphics, m_transform);
}

void Enemy::OnCollision(Actor* actor) {
	if (actor->GetType() == eType::PROJECTILE);
	{
		m_destroy = true;
		nc::Color color = Color(rand()%256, rand() % 256, rand() % 256);

		particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 100, 200);
	}
}

bool Enemy::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open()) {
		success = true;

		//m_transform "filename"
		//m_shape "filename"

		Actor::Load(stream);
		stream >> m_thrust;
	}

	return success;
}
