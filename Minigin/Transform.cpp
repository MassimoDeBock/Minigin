#include "MiniginPCH.h"
#include "Transform.h"

dae::Transform::Transform()
{
}

dae::Transform::Transform(float x, float y, float z)
{
	SetPosition(x, y, z);
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

dae::Transform dae::Transform::operator+(Transform& right)
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
