#include "Game.h"

namespace nc {
	

	bool nc::Game::Update(float dt)
	{
		m_frametime += dt;
		bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

		switch (m_state) {
		case Game::eState::INIT:
			break;
		case Game::eState::TITLE:
			if (Core::Input::IsPressed(VK_SPACE)) {
				m_state = eState::START_GAME;
			}
			break;
		case Game::eState::START_GAME:
		{
			Player* ship = new Player;
			ship->Load("ship.txt");
			scene.AddActor(ship);

			for (size_t i = 0; i < 3; i++) {
				Actor* enemy = new Enemy;
				enemy->Load("enemy.txt");
				dynamic_cast<Enemy*>(enemy)->SetTarget(ship);
				dynamic_cast<Enemy*>(enemy)->SetThrust(random(20, 100));
				enemy->GetTransform().RandomizePos();
				scene.AddActor(enemy);
			}
			m_state = eState::GAME;
		}
			break;
		case Game::eState::GAME:
			m_spawnTime += dt;
			if (m_spawnTime >= 3.0f) {
				m_spawnTime = 0;
				Actor* enemy = new Enemy;
				enemy->Load("enemy.txt");
				Actor* target = scene.GetActor<Player>();
				if (target != nullptr) dynamic_cast<Enemy*>(enemy)->SetTarget(target);
				dynamic_cast<Enemy*>(enemy)->SetThrust(random(20, 100));
				enemy->GetTransform().RandomizePos();
				scene.AddActor(enemy);
			}
			break;
		case Game::eState::GAME_OVER:
			break;
		default:
			break;
		}
		


		particleSystem.Update(dt);
		scene.Update(dt);
		return quit;
	}

	void nc::Game::Draw(Core::Graphics& graphics)
	{

		switch (m_state) {
		case Game::eState::INIT:
			break;
		case eState::TITLE: {
			graphics.SetColor(Color(0, 255, 0));
			graphics.DrawString(350, 300, "Pew Pew time");
		}
			break;
		case Game::eState::START_GAME:
			break;
		case Game::eState::GAME:
			graphics.SetColor(Color(255, 255, 255));
			graphics.DrawString(700, 10, std::to_string(m_score).c_str());
			break;
		case Game::eState::GAME_OVER:
			graphics.SetColor(Color(255, 0, 0));
			graphics.DrawString(350, 300, "GAME OVER");
		}

		particleSystem.Draw(graphics);
		scene.Draw(graphics);
	}

	void nc::Game::Startup()
	{
		DWORD ticks = GetTickCount();
		//std::cout << ticks / 1000 / 60 / 60 << std::endl;
		particleSystem.Startup();

		
	}
	void Game::Shutdown()
	{
	}
}
