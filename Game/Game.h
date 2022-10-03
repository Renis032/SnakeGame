#pragma once

#include "SFML/Graphics/RenderWindow.hpp"

#include "../ResourceManager/ResourceManager.h"
#include "../State/StateManager.h"

#include <memory>

struct Context
{
    Context();

    std::unique_ptr<Core::ResourceManager> resources = std::make_unique<Core::ResourceManager>();
    std::unique_ptr<Engine::StateManager> states = std::make_unique<Engine::StateManager>();
    std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>();

};

class Game
{
public:
    Game();
    ~Game() = default;

    void Run();
private:
    std::shared_ptr<Context> m_context = std::make_shared<Context>();
    const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
};
