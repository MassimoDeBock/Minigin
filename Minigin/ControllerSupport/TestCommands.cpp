#include "TestCommands.h"
#include <iostream>

void dae::JumpCommand::execute()
{
	std::cout << "Jump Command executed" << std::endl;
}

void dae::FireCommand::execute()
{
	std::cout << "Fire Command executed" << std::endl;
}

void dae::DuckCommand::execute()
{
	std::cout << "Duck Command executed" << std::endl;
}

void dae::FartCommand::execute()
{
	std::cout << "Fart Command executed" << std::endl;
}
