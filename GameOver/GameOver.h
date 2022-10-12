#pragma once

#include <SFML/Graphics/Text.hpp>

#include "../Game/Game.h"
#include "../State/State.h"

class GameOver : public Engine::State
{
public:
    GameOver(std::shared_ptr<Context>& context);

    void Init() override;
    void ProccesInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameOverTitle;
    sf::Text m_retryButton;
    sf::Text m_exitButton;

    bool m_isRetryButtonSelected = true;
    bool m_isRetryButtonPressed = false;

    bool m_isExitButtonSelected = false;
    bool m_isExitButtonPressed = false;
};
