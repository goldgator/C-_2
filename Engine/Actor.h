#pragma once
#include "Transform.h"
#include "Shape.h"


namespace nc {
	class Scene;

	class Actor {
	public:
		enum class eType
		{
			PLAYER,
			ENEMY,
			PROJECTILE
		};


	public:
		Actor() : m_transform{ Transform() }, m_shape{ Shape() } {};
		Actor(Transform transform, Shape shape) : m_transform{ transform }, m_shape{ shape } {};
		virtual ~Actor() {}

		virtual eType GetType() = 0;

		virtual void OnCollision(Actor* actor) {}

		void Set(Transform transform, Shape shape) { m_transform = transform; m_shape = shape; };

		virtual void Update(float dt);

		virtual void Draw(Core::Graphics& graphics);

		virtual bool Load(const std::string& filename);
		virtual bool Load(std::istream& stream);

		void SetScene(Scene* scene) { m_scene = scene; };

		Transform& GetTransform() { return m_transform; }
		void SetTransform(Transform transform) { m_transform = transform; }

		Shape& GetShape() { return m_shape; }
		void SetShape(Shape shape) { m_shape = shape; }

		void SetDestroy(bool destroy) { m_destroy = destroy; }
		bool IsDestroy() { return m_destroy; }

		float GetRadius();

	public:
		Scene* m_scene{ nullptr };
		Transform m_transform;
		Shape m_shape;
		bool m_destroy{false};
	};
}