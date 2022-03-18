#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"



dae::GameObject::GameObject() 
{
}


dae::GameObject::~GameObject() {
	for (auto& it : m_Components) {
		delete it.second;
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

void dae::GameObject::BeginPlay()
{
	for (auto const& x : m_Components) {
		x.second->BeginPlay();
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

void dae::GameObject::SetRelativeTransform(float x, float y)
{
	SetRelativeTransform(Transform(x, y, 0.f));
}

void dae::GameObject::SetRelativeTransform(const Transform& pos)
{
	m_RelativeTransform.SetPosition(pos);
	SetTransformDirty();
}

void dae::GameObject::SetAbsoluteTransform(float x, float y)
{
	SetAbsoluteTransform(Transform(x, y, 0.f));
}

void dae::GameObject::SetAbsoluteTransform(const Transform& pos)
{
	if (m_pParent == nullptr) {
		m_RelativeTransform.SetPosition(pos);
	}
	else {
		m_RelativeTransform.SetPosition(Transform(pos.GetPosition() - m_pParent->GetAbsoluteTransform().GetPosition()));
	}
	SetTransformDirty();
}

void dae::GameObject::UpdateAbsoluteTransform()const
{
	if (m_TransformIsDirty) {
		if (m_pParent == nullptr) {
			m_AbsoluteTransform = m_RelativeTransform;
		}
		else {
			m_AbsoluteTransform = m_pParent->GetAbsoluteTransform() + m_RelativeTransform;
		}
	}
	m_TransformIsDirty = false;
}

void dae::GameObject::AddTransform(const Transform& translation)
{
	m_RelativeTransform + translation;
	SetTransformDirty();
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

dae::Transform dae::GameObject::GetRelativeTransform() const
{
	return m_RelativeTransform;
}

dae::Transform dae::GameObject::GetAbsoluteTransform() const
{
	if (m_TransformIsDirty) {
		UpdateAbsoluteTransform();
	}
	return m_AbsoluteTransform;
}

void dae::GameObject::SetTransformDirty()
{
	m_TransformIsDirty = true;
}

void dae::GameObject::SetParent(GameObject* newParent, bool AbsoluteTransformStays)
{
	if (m_pParent == nullptr) {
		SetRelativeTransform(GetAbsoluteTransform());
	}
	else {
		if (AbsoluteTransformStays) {
			SetRelativeTransform(GetRelativeTransform() - m_pParent->GetAbsoluteTransform());
		}
		SetTransformDirty();
	}
	if (m_pParent) {
		m_pParent->RemoveChild(this);
	}
	m_pParent = newParent;
	if (m_pParent) {
		m_pParent->AddChild(this);
	}
}

void dae::GameObject::RemoveChild(GameObject* oldChild)
{
	m_Children.erase(oldChild);
}

void dae::GameObject::AddChild(GameObject* newChild)
{
	m_Children.insert(newChild);
}

