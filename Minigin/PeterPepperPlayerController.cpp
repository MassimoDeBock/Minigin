#include "MiniginPCH.h"
#include "PeterPepperPlayerController.h"
#include "GameObject.h"
#include "MovementComponent.h"

dae::PeterPepperPlayerController::PeterPepperPlayerController(const int playerID)
	:BasePlayerController(playerID)
{
}

dae::PeterPepperPlayerController::~PeterPepperPlayerController()
{
}

void dae::PeterPepperPlayerController::Update()
{
}

void dae::PeterPepperPlayerController::Render() const
{
}

void dae::PeterPepperPlayerController::OnAssign()
{
	m_MovementComponent = new MovementComponent();
	m_GameObjectRef->AddComponent("MovementComponent", m_MovementComponent);
}
