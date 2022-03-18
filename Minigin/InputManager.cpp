#include "MiniginPCH.h"
#include "InputManager.h"
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")
#include <Windows.h>
#include <iostream>
#include "Command.h"
#include <Xinput.h>
#include "CommandList.h"
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



bool dae::InputManager::ProcessInput()
{
	// todo: read the input
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
		pimpl->commandList.at(i)->ProcessInput();
	}
	return true;
}

bool dae::InputManager::HandleInput()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
		pimpl->commandList.at(i)->HandleInput();

	}
	return true;
}

void dae::InputManager::CheckConnections()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
		// Simply get the state of the controller from XInput.
		pimpl->commandList.at(i)->CheckConnection();
	}
}