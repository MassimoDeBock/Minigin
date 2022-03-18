#pragma once
#include <unordered_map>
#include "ControllerButtons.h"
#include "Command.h"
#include <memory>


namespace dae {
	class CommandList
	{
	public:
		CommandList();
		~CommandList();

		void CheckConnection();
		void SetUserNumber(unsigned int num);

		void CheckPressedCommand();
		void CheckDownCommand();
		void CheckReleasedCommand();
		void CheckUpCommand();

		void ProcessInput();
		void HandleInput();

		bool IsPressed(ControllerButton button)const;
		bool IsDown(ControllerButton button)const;
		bool IsReleased(ControllerButton button)const;
		bool IsUp(ControllerButton button)const;

		/*void UpdateController(XINPUT_STATE* currentControllerState);*/

		//Pressed
		void AddPressedCommand(ControllerButton buttonID, Command* command);
		void RemovePressedCommand(ControllerButton buttonID);

		//Down
		void AddDownCommand(ControllerButton buttonID, Command* command);
		void RemoveDownCommand(ControllerButton buttonID);

		//Released
		void AddReleasedCommand(ControllerButton buttonID, Command* command);
		void RemoveReleasedCommand(ControllerButton buttonID);

		//Up
		void AddUpCommand(ControllerButton buttonID, Command* command);
		void RemoveUpCommand(ControllerButton buttonID);

	private:
		struct Controller;
		std::unique_ptr<Controller> m_Controller;

		int m_UserNumber{};
		std::unordered_map<ControllerButton, Command*> m_PressedCommands;
		std::unordered_map<ControllerButton, Command*> m_DownCommands;
		std::unordered_map<ControllerButton, Command*> m_ReleasedCommands;
		std::unordered_map<ControllerButton, Command*> m_UpCommands;
	};
}