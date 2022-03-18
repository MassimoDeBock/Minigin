#pragma once
#include "Command.h"

namespace dae {
	class ExitCommand : public Command {
	public:
		ExitCommand(bool* pDoContinue) 
			:m_pDoContinue(pDoContinue)
		{}
		bool* m_pDoContinue;
		virtual void execute() {
			if (m_pDoContinue == nullptr) {
				return;
			}
			*m_pDoContinue = false;
		}
	};
}