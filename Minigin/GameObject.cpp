#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"



dae::GameObject::GameObject() {
	m_RelativeTransform = std::make_shared<Transform>();
}


dae::GameObject::~GameObject() {
	for (auto& it : m_Components) {
		delete it.second;
		it.second = nullptr;
	}
	m_Components.clear();
};

void dae::GameObject::Update() {
	for (auto const& x : m_Components) {
		x.second->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (auto const& x : m_Components) {
		x.second->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (auto const& x : m_Components) {
		x.second->Render();
	}
}

void dae::GameObject::SetId(unsigned int id)
{
	if (m_id == 0) {
		m_id = id;
	}
}

void dae::GameObject::SetRelativePosition(float x, float y)
{
	m_RelativeTransform.get()->SetPosition(x, y, 0.0f);
}

void dae::GameObject::SetAbsolutePosition(float x, float y)
{
	if (!m_OriginTransform.expired())
	{
		Transform pos = Transform(x, y, 0) - *m_OriginTransform.lock().get();
		m_RelativeTransform.get()->SetPosition(pos.GetPosition().x, pos.GetPosition().y, pos.GetPosition().z);
	}
	else {
		m_RelativeTransform.get()->SetPosition(x, y, 0.0f);
	}
}

template<typename T>
T* dae::GameObject::GetComponent() const
{
	std::unordered_map<std::type_index, Component*>::const_iterator compIt = m_Components.find(typeid(T))->second;
	if (compIt != m_Components.end) {
		return T(compIt);
	}
	return nullptr;
}

dae::Transform dae::GameObject::GetAbsoluteTransform() const
{
	if (!m_OriginTransform.expired())
	{
		return Transform(*m_RelativeTransform.get() + *m_OriginTransform.lock().get());
	}
	return *m_RelativeTransform.get();
}

