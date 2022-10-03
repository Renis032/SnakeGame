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

    m_grass.setTexture(m_context->resources->GetTexture("grass"));
    m_grass.setTextureRect(m_context->window->getViewport(m_context->window->getDefaultView()));

//    m_food.setTexture(m_context->resources->GetTexture("food"));
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
    }
}

void GamePlay::Update(sf::Time deltaTime)
{

}

void GamePlay::Draw()
{
    m_context->window->clear();
    m_context->window->draw(m_grass);
    m_context->window->display();
}

void GamePlay::Pause()
{

}

void GamePlay::Start()
{

}
