#include "MiniginPCH.h"
#include "Component.h"


dae::Component::Component(GameObject& parentGameObjectRef) 
	:m_GameObjectRef(&parentGameObjectRef)
{
}