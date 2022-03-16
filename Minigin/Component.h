#pragma once

namespace dae {
	class GameObject;
	class Component
	{
		//functions
	public:
		Component(GameObject& parentGameObject);


		Component() = delete;
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	private:


		//variables
	public:
		virtual void Update() = 0;
		virtual void Render()const = 0;

	protected:
		GameObject* m_GameObjectRef;

	};
}
