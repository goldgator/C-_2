#pragma once
#include "core.h"
#include <cmath>
#include <string>
#include <vector>
#include "Shape.h"
#include "Vector2.h"
#include "Actor.h"
#include "MathExt.h"
#include "Player.h"
#include "Enemy.h"
#include <list>
#include <vector>
#include "Scene.h"
#include "ParticleSystem.h"




namespace nc {
	class Game {
	public:
		enum class eState {
			INIT,
			TITLE,
			START_GAME,
			GAME,
			GAME_OVER
		};


		void Startup();
		void Shutdown();

		bool Update(float dt);
		void Draw(Core::Graphics& graphics);

		void AddPoints(int points) { m_score += points; }


	private:
		eState m_state{ eState::TITLE };
		int m_lives{ 3 };
		int m_score{ 0 };

		Scene scene;

		float t{ 0 };

		float m_frametime{0};
		float m_spawnTime{0};
	};



}

