#pragma once

#include "../State/State.h"
#include "../Game/Game.h"

#include <SFML/Graphics/Text.hpp>

class PauseMenu : public Engine::State
{
public:
    PauseMenu(std::shared_ptr<Context>& context);

    void Init() override;
    void ProccesInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;

private:
    std::shared_ptr<Context> m_context;

    sf::Text m_pauseTitle;
    sf::Text m_resumeButton;
    sf::Text m_exitButton;

    bool m_isResumeButtonSelected = true;
    bool m_isResumeButtonPressed = false;

    bool m_isExitButtonSelected = false;
    bool m_isExitButtonPressed = false;
};
