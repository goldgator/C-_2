#include "Projectile.h"
#include "MathExt.h"
#include "ParticleSystem.h"

using namespace nc;

void Projectile::Update(float dt)
{
	Vector2 force = Vector2::Rotate(Vector2(1, 0), m_transform.GetAngle()) * m_thrust;
	velocity = velocity + (force * dt);
	m_transform.SetPosition(m_transform.GetPosition() + (velocity * dt));
	if (force.LengthSqr() > 0)
	{
		particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 10, 1, nc::Color(255, 0, 0), 1, 100, 200);
	}

	m_destroy = (m_transform.position.x > 800 || m_transform.position.x < 0 || m_transform.position.y > 600 || m_transform.position.x < 0);
	

	m_transform.Update();
}

void Projectile::Draw(Core::Graphics& graphics)
{
	m_shape.Draw(graphics, m_transform);
}

void Projectile::OnCollision(Actor* actor) {
	if (actor->GetType() == eType::ENEMY) {
		m_destroy = true;
	}
};

bool Projectile::Load(const std::string& filename)
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
