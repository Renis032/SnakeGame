#include "Game.h"

#include "../MainMenu/MainMenu.h"

Context::Context()
{
    resources = std::make_unique<Core::ResourceManager>();
    states = std::make_unique<Engine::StateManager>();
    window = std::make_unique<sf::RenderWindow>();
}

Game::Game()
{
    m_context->window->create(sf::VideoMode(1280, 720), "Snake", sf::Style::Close);
    m_context->window->setVerticalSyncEnabled(true);

    m_context->states->AddState(std::make_unique<MainMenu>(m_context));
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while(m_context->window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        while(timeSinceLastFrame > timePerFrame)
        {
            timeSinceLastFrame -= timePerFrame;

            m_context->states->ProcessStateChange();
            m_context->states->GetCurrentState()->ProccesInput();
            m_context->states->GetCurrentState()->Update(timePerFrame);
            m_context->states->GetCurrentState()->Draw();
        }
    }
}

