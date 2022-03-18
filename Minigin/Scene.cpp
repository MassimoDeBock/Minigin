#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name, float fixedTimeStep) : m_Name(name), m_deltaTime(0.0f), m_FixedTimeStep(fixedTimeStep) {}
Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>&object)
{

	object.get()->setSceneRef(*this);
	m_Objects.push_back(object);
}

void Scene::Update(float deltaTime)
{
	m_deltaTime = deltaTime;
	for (auto& object : m_Objects)
	{
		object->Update();
	}
}

void dae::Scene::FixedUpdate()
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
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

