#pragma once

#include <stack>
#include <memory>

#include "State.h"

namespace Engine
{

    class StateManager
    {
    public:
        StateManager() = default;
        ~StateManager() = default;

        void AddState(std::unique_ptr<State> toAdd, bool replace = false);
        void PopCurrentState();
        void ProcessStateChange();
        auto GetCurrentState() -> std::unique_ptr<State>&;
    private:
        std::stack<std::unique_ptr<State>> m_stateStack;
        std::unique_ptr<State> m_newState;

        bool m_add = false;
        bool m_replace = false;
        bool m_remove = false;
    };

} // Engine
