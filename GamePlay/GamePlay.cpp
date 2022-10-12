#include "GamePlay.h"

#include <SFML/Window/Event.hpp>

#include "../Common/Common.hpp"
#include "../GameOver/GameOver.h"
#include "../PauseMenu/PauseMenu.h"

#include <random>

GamePlay::GamePlay(std::shared_ptr<Context>& context) : m_context(context)
{
    srand(time(nullptr));
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
    m_food.setOrigin(m_food.getGlobalBounds().top / 2, m_food.getGlobalBounds().left / 2);
    m_food.setScale(0.8f, 0.8f);
    int x = Common::Math::clamp<int>(rand() % m_context->window->getSize().x, 16, m_context->window->getSize().x - 2* 16);
    int y = Common::Math::clamp<int>(rand() % m_context->window->getSize().y, 16, m_context->window->getSize().y - 2* 16);

    m_food.setPosition(sf::Vector2f(x, y));

    m_snake.Init(m_context->resources->GetTexture("snake"));

    m_scoreText.setFont(m_context->resources->GetFont("mainFont"));
    m_scoreText.setCharacterSize(15);
    m_scoreText.setOutlineColor(sf::Color::Black);
    m_scoreText.setOutlineThickness(3.0f);
    m_scoreText.setString("Score: " + std::to_string(m_score));
}

void GamePlay::ProccesInput()
{
    sf::Event event;
    while (m_context->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->window->close();
        }

        if(event.type == sf::Event::KeyPressed)
        {
            sf::Vector2f newDirection = m_snakeDirection;
            switch (event.key.code)
            {
                case sf::Keyboard::Up:
                {
                    newDirection = {0.0f, -16.0f};
                    break;
                }
                case sf::Keyboard::Down:
                {
                    newDirection = {0.0f, 16.0f};
                    break;
                }
                case sf::Keyboard::Left:
                {
                    newDirection = {-16.0f, 0.0f};
                    break;
                }
                case sf::Keyboard::Right:
                {
                    newDirection = {16.0f, 0.0f};
                    break;
                }
                case sf::Keyboard::Escape:
                {
                    m_context->states->AddState(std::make_unique<PauseMenu>(m_context));
                    break;
                }
                default:
                {
                    break;
                }
            }

            if(std::abs(m_snakeDirection.x) != std::abs(newDirection.x) || std::abs(m_snakeDirection.y) != std::abs(newDirection.y))
            {
                m_snakeDirection = newDirection;
            }
        }
    }
}

void GamePlay::Update(sf::Time deltaTime)
{
    m_elapsedTime += deltaTime;
    if(m_elapsedTime.asSeconds() > 0.1f)
    {

        for (const auto& wall : m_walls)
        {
            if (m_snake.isColliding(wall))
            {
                m_context->states->AddState(std::make_unique<GameOver>(m_context), true);
                break;
            }
        }

        if(m_snake.isColliding(m_food))
        {
            m_score++;
            m_scoreText.setString("Score: " + std::to_string(m_score));
            m_snake.Grow(m_snakeDirection);

            int x = Common::Math::clamp<int>(rand() % m_context->window->getSize().x, 16, m_context->window->getSize().x - 2* 16);
            int y = Common::Math::clamp<int>(rand() % m_context->window->getSize().y, 16, m_context->window->getSize().y - 2* 16);

            m_food.setPosition(sf::Vector2f(x, y));
        }
        else
        {
            m_snake.Move(m_snakeDirection);
        }

        if(m_snake.isSelfColliding())
        {
            m_context->states->AddState(std::make_unique<GameOver>(m_context), true);
        }

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
    m_context->window->draw(m_scoreText);
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
