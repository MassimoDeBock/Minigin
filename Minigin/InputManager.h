#pragma once
#include "ControllerButtons.h"
#include "Singleton.h"
#include "Command.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		void AddPressedCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, Command* command);
		void SwapPressedCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, Command* command);

		bool ProcessInput();
		bool HandleInput();
		void CheckConnections();

	private:


		struct Impl;
		std::unique_ptr<Impl> pimpl;
	};
}
