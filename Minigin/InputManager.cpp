#include "MiniginPCH.h"
#include "InputManager.h"
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")
#include <Windows.h>
#include <iostream>
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

	std::vector<CommandList*> commandList;
};


void dae::InputManager::SetTestCommands(unsigned int i)
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
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
		pimpl->commandList.at(i)->ProcessInput();
	}
}

bool dae::InputManager::HandleInput()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
		pimpl->commandList.at(i)->HandleInput();
	}
	return false;
}

void dae::InputManager::CheckConnections()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
		pimpl->commandList.at(i)->CheckConnection();
	}
}
