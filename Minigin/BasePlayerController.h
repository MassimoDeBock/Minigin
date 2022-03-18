#pragma once
#include "Component.h"

namespace dae {
    class InputManager;
    class BasePlayerController :
        public Component
    {
    public:
        BasePlayerController(const int playerID);
        virtual ~BasePlayerController();

        int GetPlayerID();
    private:
        const int m_PlayerID;
        InputManager& m_Inputmanager;
    };
    
}