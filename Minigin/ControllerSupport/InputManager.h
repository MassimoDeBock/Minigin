#pragma once
#include "ControllerButtons.h"
#include <memory>
#include "Command.h"

namespace dae
{
	//class Command;


	class InputManager
	{
	public:
		InputManager();
		~InputManager();


		void SetDefaultCommands(unsigned int i);
		void AddPressedCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, Command* command);
		void SwapPressedCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, Command* command);

		void ProcessInput();
		bool HandleInput();
		//bool IsPressed(ControllerButton button, const int userNumber) const;
		//bool IsDown(ControllerButton button, const int userNumber) const;
		//bool IsUp(ControllerButton button, const int userNumber) const;
		void CheckConnections();


	private:
		struct Impl;
		std::unique_ptr<Impl> pimpl;
	};
}