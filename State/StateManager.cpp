#include "StateManager.h"

void Engine::StateManager::AddState(std::unique_ptr<Engine::State> toAdd, bool replace)
{
    m_add = true;
    m_newState = std::move(toAdd);

    m_replace = replace;
}

void Engine::StateManager::PopCurrentState()
{
    m_remove = true;
}

void Engine::StateManager::ProcessStateChange()
{
    if(m_remove && false == m_stateStack.empty())
    {
        m_stateStack.pop();

        if(false == m_stateStack.empty())
        {
            m_stateStack.top()->Start();
        }

        m_remove = false;
    }

    if(m_add)
    {
        if(m_replace && false == m_stateStack.empty())
        {
            m_stateStack.pop();
            m_replace = false;
        }

        if(false == m_stateStack.empty())
        {
            m_stateStack.top()->Pause();
        }

        m_stateStack.push(std::move(m_newState));
        m_stateStack.top()->Init();
        m_stateStack.top()->Start();
        m_add = false;
    }
}

auto Engine::StateManager::GetCurrentState() -> std::unique_ptr<Engine::State>&
{
    return m_stateStack.top();
}
