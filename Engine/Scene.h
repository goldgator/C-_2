#pragma once
#include "core.h"
#include <vector>
#include <list>

namespace nc 
{
	class Scene
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void AddActor(class Actor* actor);
		void RemoveActor(class Actor* object);

		template <typename T>
		T* GetActor() 
		{
			nc::Actor* result{ nullptr };

			for (nc::Actor* actor : m_actors)
			{
				result = dynamic_cast<T*>(actor);
				if (result) break;
			}

			return dynamic_cast<T*>(result);
		}

		template <typename T>
		std::vector<nc::Actor*> GetActors()
		{
			std::vector<nc::Actor*> results;

			for (nc::Actor* actor : m_actors)
			{
				T* result = dynamic_cast<T*>(actor);
				if (result)
				{
					results.push_back(result);
				}
			}

			return dynamic_cast<T*>(results);
		}

	private:
		std::list<class Actor*> m_actors;

	};
}