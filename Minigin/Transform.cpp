#include "MiniginPCH.h"
#include "Transform.h"

dae::Transform::Transform()
{
}

dae::Transform::Transform(float x, float y, float z)
{
	SetPosition(x, y, z);
}

dae::Transform::Transform(glm::vec3 vec3)
	:m_Position(vec3)
{
}

dae::Transform::Transform(const Transform& transform)
	: m_Position(transform.GetPosition())
{
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::Transform::SetPosition(const Transform& transform)
{
	m_Position = transform.GetPosition();
}

dae::Transform dae::Transform::operator+(Transform& right)
{
	return Transform(
		this->GetPosition().x + right.GetPosition().x,
		this->GetPosition().y + right.GetPosition().y,
		this->GetPosition().z + right.GetPosition().z
	);
}

dae::Transform dae::Transform::operator+(const Transform& right)
{
	return Transform(
		this->GetPosition().x + right.GetPosition().x,
		this->GetPosition().y + right.GetPosition().y,
		this->GetPosition().z + right.GetPosition().z
	);
}

dae::Transform dae::Transform::operator-(Transform& right)
{
	return Transform(
		this->GetPosition().x - right.GetPosition().x,
		this->GetPosition().y - right.GetPosition().y,
		this->GetPosition().z - right.GetPosition().z
	);
}

dae::Transform dae::Transform::operator-(const Transform& right)
{
	return Transform(
		this->GetPosition().x - right.GetPosition().x,
		this->GetPosition().y - right.GetPosition().y,
		this->GetPosition().z - right.GetPosition().z
	);
}
