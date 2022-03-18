#pragma once
#include "SceneManager.h"
#include "Component.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<SceneObject>& object);

		void Update(float deltaTime);
		void FixedUpdate();
		void Render() const;
		float GetDeltaTime();
		float GetFixedTimeStep();

		unsigned int AssignId();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		explicit Scene(const std::string& name, float fixedTimeStep);

		float m_deltaTime;
		const float m_FixedTimeStep;
		std::string m_Name;
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};
		//	std::vector <std::pair<unsigned int,GraphicsComponent*>> m_GraphicsComponents{};
		unsigned int m_objIdCounter{ 0 };

		static unsigned int m_IdCounter;
	};

}
