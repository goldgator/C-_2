#include "pch.h"
#include "Actor.h"
#include "color.h"


namespace nc {

	bool Actor::Load(const std::string& filename) {
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open()) {
			success = true;

			//m_transform "filename"
			//m_shape "filename"

			stream >> m_transform;

			string name;
			stream >> name;
			m_shape.Load(name);

		}

		return success;
	}

	bool Actor::Load(std::istream& stream)
	{

		//m_transform "filename"
		//m_shape "filename"

		stream >> m_transform;

		string name;
		stream >> name;
		m_shape.Load(name);

		return true;
	}

	void Actor::Update(float dt)
	{
	}

	void Actor::Draw(Core::Graphics& graphics) {
		m_shape.Draw(graphics, m_transform);
	}

	float Actor::GetRadius() {
		return m_shape.GetRadius() * m_transform.scale;
	}
}