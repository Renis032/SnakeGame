#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "../State/State.h"
#include "../Game/Game.h"

class MainMenu : public Engine::State
{
public:
    MainMenu(std::shared_ptr<Context>& context);

    void Init() override;
    void ProccesInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;

private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameTitle;
    sf::Text m_playButton;
    sf::Text m_exitButton;

    bool m_isPlayButtonSelected = true;
    bool m_isPlayButtonPressed = false;

    bool m_isExitButtonSelected = false;
    bool m_isExitButtonPressed = false;
};
