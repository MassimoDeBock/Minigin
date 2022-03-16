#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"



dae::GameObject::GameObject() {
	m_RelativeTransform = std::make_shared<Transform>();
}


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update() {
	for (auto const& x : m_Components) {
		x.second.get()->Update();
	}
}

void dae::GameObject::Render() const
{
	for (auto const& x : m_Components) {
		x.second.get()->Render();
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

void dae::GameObject::AddComponent(const std::shared_ptr<Component> component)
{
	std::type_index id{ typeid(component.get()) };
	std::shared_ptr<Component> ow = component;
	m_Components.insert(std::pair<std::type_index, std::shared_ptr<Component>>(typeid(component.get()), component));
}

//template<typename T>
//void dae::GameObject::AddComponent(const std::shared_ptr<T> component)
//{
//
//	m_Components.insert(std::make_pair<std::type_index, std::shared_ptr<T>>(typeid(component.get()), component));
//
//}

template<typename T>
inline std::weak_ptr<T> dae::GameObject::getComponent()
{
	auto componentFound{ m_Components.find(std::type_index(typeid(T))) };
	if (componentFound != m_Components.end()) {
		return componentFound->second;
	}
	return std::weak_ptr<T>();
}

dae::Transform dae::GameObject::GetAbsoluteTransform() const
{
	if (!m_OriginTransform.expired())
	{
		return Transform(*m_RelativeTransform.get() + *m_OriginTransform.lock().get());
	}
	return *m_RelativeTransform.get();
}