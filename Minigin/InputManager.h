#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <memory>
#include "Command.h"
#include "ControllerButtons.h"

namespace dae
{
	class Command;

	class InputManager final : public Singleton<InputManager>

	{
	public:
		InputManager();
		~InputManager();


		void SetTestCommands(unsigned int i);
		void AddPressedCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, Command* command);
		void SwapPressedCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, Command* command);

		void ProcessInput();
		bool HandleInput();
		void CheckConnections();


	private:
		struct Impl;
		std::unique_ptr<Impl> pimpl;
	};

}
