#include "InputManager.h"
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")
#include <Windows.h>
#include <iostream>
#include "Command.h"
#include <Xinput.h>
#include "CommandList.h"
#include "TestCommands.h"
#include <vector>

struct dae::InputManager::Impl
{
	dae::InputManager::Impl()
	{
		for (unsigned int i = 0; i < XUSER_MAX_COUNT; ++i) {
			commandList.push_back(new CommandList());
			commandList.at(i)->SetUserNumber(i);
		}
	}

	~Impl() {
		for (auto it = std::begin(commandList); it != std::end(commandList); ++it) {
			delete* it;
		}
	}

	//bool isConnected[XUSER_MAX_COUNT]{ false };

	std::vector<CommandList*> commandList;
};


void dae::InputManager::SetDefaultCommands(unsigned int i)
{
	std::cout << "default commands added for: " << i << " \n";
	pimpl->commandList.at(i)->AddPressedCommand(dae::ControllerButton::A, new FireCommand());
	pimpl->commandList.at(i)->AddPressedCommand(dae::ControllerButton::B, new JumpCommand());
	pimpl->commandList.at(i)->AddPressedCommand(dae::ControllerButton::X, new DuckCommand());
	pimpl->commandList.at(i)->AddPressedCommand(dae::ControllerButton::Y, new FartCommand());
}

void dae::InputManager::AddPressedCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, Command* command)
{
	pimpl->commandList.at(controllerNumber)->AddPressedCommand(buttonID, command);
}

void dae::InputManager::SwapPressedCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, Command* command)
{
	pimpl->commandList.at(controllerNumber)->RemovePressedCommand(buttonID);
	AddPressedCommandsToController(controllerNumber, buttonID, command);
}


dae::InputManager::InputManager()
	: pimpl(new Impl())
{}

dae::InputManager::~InputManager()
{
}



void dae::InputManager::ProcessInput()
{
	// todo: read the input
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
		pimpl->commandList.at(i)->ProcessInput();
	}
}

bool dae::InputManager::HandleInput()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
		pimpl->commandList.at(i)->HandleInput();


		//if (IsPressed(ControllerButton::A, i)) {
		//	//std::cout << "Button A has been pressed" << std::endl;
		//	pimpl->buttonA_->execute();
		//}
		//else if (IsPressed(ControllerButton::B, i)) {
		//	//std::cout << "Button B has been pressed" << std::endl;
		//	pimpl->buttonB_->execute();
		//}
		//else if (IsPressed(ControllerButton::Y, i)) {
		//	//std::cout << "Button Y has been pressed" << std::endl;
		//	pimpl->buttonY_->execute();
		//}
		//else if (IsPressed(ControllerButton::X, i)) {
		//	//std::cout << "Button X has been pressed" << std::endl;
		//	pimpl->buttonX_->execute();
		//	//remove this in game when there is a different quit option
		//	return true;
		//}
	}
	return false;
}
//
//bool dae::InputManager::IsPressed(ControllerButton button, const int userNumber) const
//{
//	// todo: return whether the given button is pressed or not.
//	if (!(DWORD(pimpl->previousState[userNumber].Gamepad.wButtons) & DWORD(button)) && (DWORD(pimpl->state[userNumber].Gamepad.wButtons) & DWORD(button))) {
//		return true;
//	}
//
//	return false;
//}
//
//bool dae::InputManager::IsDown(ControllerButton button, const int userNumber) const
//{
//	if (DWORD(pimpl->state[userNumber].Gamepad.wButtons) & DWORD(button)) {
//		return true;
//	}
//
//	return false;
//}
//
//bool dae::InputManager::IsUp(ControllerButton button, const int userNumber) const
//{
//	if (DWORD(pimpl->state[userNumber].Gamepad.wButtons) & DWORD(button)) {
//		return false;
//	}
//
//	return true;
//}



void dae::InputManager::CheckConnections()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
		// Simply get the state of the controller from XInput.
		pimpl->commandList.at(i)->CheckConnection();
	}
}