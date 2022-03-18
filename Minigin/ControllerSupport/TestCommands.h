#pragma once
#include "Command.h"

namespace dae {
	class JumpCommand : public Command {
	public:
		virtual void execute() override;
	};

	class FireCommand : public Command {
	public:
		virtual void execute() override;
	};

	class DuckCommand : public Command {
	public:
		virtual void execute() override;
	};

	class FartCommand : public Command {
	public:
		virtual void execute() override;
	};
}
