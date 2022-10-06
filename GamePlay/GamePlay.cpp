#include "GamePlay.h"

#include <SFML/Window/Event.hpp>

GamePlay::GamePlay(std::shared_ptr<Context>& context) : m_context(context)
{
}

void GamePlay::Init()
{
    m_context->resources->LoadResource("food", "/home/default/projects/SnakeGame/assets/textures/food.png");
    m_context->resources->LoadResource("wall", "/home/default/projects/SnakeGame/assets/textures/wall.png");
    m_context->resources->LoadResource("grass", "/home/default/projects/SnakeGame/assets/textures/grass.png");
    m_context->resources->LoadResource("snake", "/home/default/projects/SnakeGame/assets/textures/snake.png");

    auto& texture = m_context->resources->GetTexture("grass");
    texture.setRepeated(true);
    m_grass.setTexture(texture);
    m_grass.setTextureRect(m_context->window->getViewport(m_context->window->getDefaultView()));

    m_walls.resize(4);
    for (auto& wall : m_walls)
    {
        auto& wallTexture = m_context->resources->GetTexture("wall");
        wallTexture.setRepeated(true);
        wall.setTexture(wallTexture);
    }

    m_walls.at(0).setTextureRect({0, 0, int(m_context->window->getSize().x), 16});
    m_walls.at(1).setTextureRect({0, 0, int(m_context->window->getSize().x), 16});
    m_walls.at(1).setPosition(0, m_context->window->getSize().y - 16);

    m_walls.at(2).setTextureRect({0, 0, 16, int(m_context->window->getSize().x)});
    m_walls.at(3).setTextureRect({0, 0, 16, int(m_context->window->getSize().x)});
    m_walls.at(3).setPosition(m_context->window->getSize().x - 16, 0);

    m_food.setTexture(m_context->resources->GetTexture("food"));
    m_food.setPosition(m_context->window->getSize().x / 2, m_context->window->getSize().y / 2);

    m_snake.Init(m_context->resources->GetTexture("snake"));
}

void GamePlay::ProccesInput()
{
    sf::Event event;
    while (m_context->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_context->window->close();
        }

        if(event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Up:
                {
                    m_snakeDirection = {0.0f, -16.0f};
                    break;
                }
                case sf::Keyboard::Down:
                {
                    m_snakeDirection = {0.0f, 16.0f};
                    break;
                }
                case sf::Keyboard::Left:
                {
                    m_snakeDirection = {-16.0f, 0.0f};
                    break;
                }
                case sf::Keyboard::Right:
                {
                    m_snakeDirection = {16.0f, 0.0f};
                    break;
                }
            }
        }
    }
}

void GamePlay::Update(sf::Time deltaTime)
{
    m_elapsedTime += deltaTime;
    if(m_elapsedTime.asSeconds() > 0.05f)
    {
        m_snake.Move(m_snakeDirection);
        m_elapsedTime = sf::Time::Zero;
    }
}

void GamePlay::Draw()
{
    m_context->window->clear();
    m_context->window->draw(m_grass);
    for (auto& wall : m_walls)
    {
        m_context->window->draw(wall);
    }
    m_context->window->draw(m_food);
    m_context->window->draw(m_snake);
    m_context->window->display();

}

void GamePlay::Pause()
{

}

void GamePlay::Start()
{

}
