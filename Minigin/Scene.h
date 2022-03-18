#pragma once
#include "SceneManager.h"
#include "Component.h"
#include <unordered_map>

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::string& objectName, const std::shared_ptr<GameObject>& object);
		GameObject* GetGameObjects(const std::string& objectName);

		void Update(float deltaTime);
		void FixedUpdate();
		void BeginPlay();
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

		std::unordered_map <std::string ,std::shared_ptr<GameObject>> m_GameObjects;
		unsigned int m_objIdCounter{ 0 };

		static unsigned int m_IdCounter;
	};

}
