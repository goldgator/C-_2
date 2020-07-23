#pragma once
#include "Vector2.h"
#include "color.h"

namespace nc {
	struct Particle
	{
		Vector2 position;
		Vector2 prevPosition;
		Vector2 velocity;
		Color color;
		float damping{ .98f };
		float lifetime;
		bool active{false};
	};
}

