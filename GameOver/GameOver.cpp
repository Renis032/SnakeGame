#include "GameOver.h"

#include "../GamePlay/GamePlay.h"

#include <SFML/Window/Event.hpp>

GameOver::GameOver(std::shared_ptr<Context> &context) : m_context(context)
{

}

void GameOver::Init()
{
    m_gameOverTitle.setFont( m_context->resources->GetFont("mainFont"));
    m_gameOverTitle.setString("Game Over");
    m_gameOverTitle.setCharacterSize(60);
    m_gameOverTitle.setOutlineColor(sf::Color::Black);
    m_gameOverTitle.setOutlineThickness(3.0f);
    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2, 0);
    m_gameOverTitle.setPosition(m_context->window->getSize().x / 2, m_gameOverTitle.getPosition().y / 2);


    m_retryButton.setFont( m_context->resources->GetFont("mainFont"));
    m_retryButton.setString("Retry");
    m_retryButton.setCharacterSize(40);
    m_retryButton.setOutlineColor(sf::Color::Black);
    m_retryButton.setOutlineThickness(3.0f);
    m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2, 0);
    m_retryButton.setPosition(m_gameOverTitle.getPosition().x, m_gameOverTitle.getPosition().y + (m_context->window->getSize().y / 4));


    m_exitButton.setFont( m_context->resources->GetFont("mainFont"));
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(40);
    m_exitButton.setOutlineColor(sf::Color::Black);
    m_exitButton.setOutlineThickness(3.0f);
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, 0);
    m_exitButton.setPosition(m_gameOverTitle.getPosition().x, m_retryButton.getPosition().y + 100);
}

void GameOver::ProccesInput()
{
    sf::Event event;
    while (m_context->window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_context->window->close();
        }
        if(event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Up:
                {
                    if(false == m_isRetryButtonSelected)
                    {
                        m_isRetryButtonSelected = true;
                        m_isExitButtonSelected = false;
                    }
                    break;
                }
                case sf::Keyboard::Down:
                {
                    if(false == m_isExitButtonSelected)
                    {
                        m_isExitButtonSelected = true;
                        m_isRetryButtonSelected = false;
                    }
                    break;
                }
                case sf::Keyboard::Return:
                {
                    m_isRetryButtonPressed = false;
                    m_isExitButtonPressed = false;

                    if(m_isRetryButtonSelected)
                    {
                        m_isRetryButtonPressed = true;
                    }
                    else if (m_isExitButtonSelected)
                    {
                        m_isExitButtonPressed = true;
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
}

void GameOver::Update(sf::Time deltaTime)
{
    sf::Color selectedColor = sf::Color::Yellow;
    if(m_isRetryButtonSelected)
    {
        m_retryButton.setFillColor(selectedColor);
        m_exitButton.setFillColor(sf::Color::White);
    }
    if(m_isExitButtonSelected)
    {
        m_exitButton.setFillColor(selectedColor);
        m_retryButton.setFillColor(sf::Color::White);
    }

    if(m_isRetryButtonPressed)
    {
        m_context->states->AddState(std::make_unique<GamePlay>(m_context));
    }
    if(m_isExitButtonPressed)
    {
        m_context->window->close();
    }
}

void GameOver::Draw()
{
//    m_context->window->clear(sf::Color::Blue);
    m_context->window->draw(m_gameOverTitle);
    m_context->window->draw(m_retryButton);
    m_context->window->draw(m_exitButton);
    m_context->window->display();
}
