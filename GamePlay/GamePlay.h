#pragma once

#include <memory>
#include <vector>

#include "../Game/Game.h"
#include "../State/State.h"

#include <SFML/Graphics/Sprite.hpp>

class GamePlay : public Engine::State
{
public:
    GamePlay(std::shared_ptr<Context>& context);

    void Init() override;
    void ProccesInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;

    void Pause() override;
    void Start() override;
private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_grass;
    sf::Sprite m_food;

    std::vector<sf::Sprite> m_walls;
};
