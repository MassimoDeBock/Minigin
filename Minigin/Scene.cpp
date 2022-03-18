#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name, float fixedTimeStep) : m_Name(name), m_deltaTime(0.0f), m_FixedTimeStep(fixedTimeStep) {}
Scene::~Scene() = default;

void Scene::Add(const std::string& objectName,const std::shared_ptr<GameObject>&object)
{
	object.get()->setSceneRef(*this);
	m_GameObjects.insert(std::pair<std::string, std::shared_ptr<GameObject>>(objectName, object));
}

GameObject* dae::Scene::GetGameObjects(const std::string& objectName)
{
	return m_GameObjects.find(objectName)->second.get();
}

void Scene::Update(float deltaTime)
{
	m_deltaTime = deltaTime;
	for (auto& object : m_GameObjects)
	{
		object.second->Update();
	}
}

void dae::Scene::FixedUpdate()
{
	for (auto& object : m_GameObjects)
	{
		object.second->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_GameObjects)
	{
		object.second->Render();
	}
}

float dae::Scene::GetDeltaTime()
{
	return m_deltaTime;
}

float dae::Scene::GetFixedTimeStep()
{
	return m_FixedTimeStep;
}

unsigned int dae::Scene::AssignId()
{
	++m_objIdCounter;
	return m_objIdCounter;
}

