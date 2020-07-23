#include "pch.h"
#include "Scene.h"
#include "Actor.h"

void nc::Scene::Startup()
{

}

void nc::Scene::Shutdown()
{
		
		for (Actor* actor : m_actors )
		{
			delete actor;
		}
		m_actors.clear();
}

void nc::Scene::Update(float dt)
{
	//check actors collisions
	std::vector<Actor*> actors{ m_actors.begin(),m_actors.end() };
	for (size_t i = 0; i < actors.size(); i++) {
		for (size_t j = i + 1; j < actors.size(); j++) {
			float distance = Vector2::Distance(actors[i]->GetTransform().GetPosition(), actors[j]->GetTransform().GetPosition());
			if (distance <= 10) {
				actors[i]->OnCollision(actors[j]);
				actors[j]->OnCollision(actors[i]);
			}
		}
	}

	//remove destroyed actors
	auto iter = m_actors.begin();
	while (iter != m_actors.end()) {
		if ((*iter)->IsDestroy()) {
			delete* iter;
			iter = m_actors.erase(iter);
		}
		else {
			iter++;
		}
	}

	//Update objects
	for (nc::Actor* actor : m_actors)
	{
		actor->Update(dt);
	}
}

void nc::Scene::Draw(Core::Graphics& graphics)
{
	for (nc::Actor* actor : m_actors)
	{
		actor->Draw(graphics);
	}
}

void nc::Scene::AddActor(Actor* actor)
{
	actor->SetScene(this);
	m_actors.push_back(actor);
}

void nc::Scene::RemoveActor(Actor* actor)
{
	std::list<Actor*>::iterator iter = std::find(m_actors.begin(), m_actors.end(), actor);
	if (iter != m_actors.end())
	{
		delete* iter;
		m_actors.erase(iter);
	}
}
