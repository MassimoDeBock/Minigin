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
		void AddCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, ButtonStates state, Command* command);
		void SwapCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, ButtonStates state, Command* command);
		void RemoveCommandsFromController(unsigned int controllerNumber, ControllerButton buttonID, ButtonStates state);

		bool ProcessInput();
		bool HandleInput();
		void CheckConnections();

	private:


		struct Impl;
		std::unique_ptr<Impl> pimpl;
	};
}
