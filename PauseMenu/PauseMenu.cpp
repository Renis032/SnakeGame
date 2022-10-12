#include "PauseMenu.h"

#include <SFML/Window/Event.hpp>

#include "../GamePlay/GamePlay.h"

PauseMenu::PauseMenu(std::shared_ptr<Context>& context) : m_context(context)
{

}

void PauseMenu::Init()
{
    m_pauseTitle.setFont( m_context->resources->GetFont("mainFont"));
    m_pauseTitle.setString("Paused");
    m_pauseTitle.setCharacterSize(60);
    m_pauseTitle.setOutlineColor(sf::Color::Black);
    m_pauseTitle.setOutlineThickness(3.0f);
    m_pauseTitle.setOrigin(m_pauseTitle.getLocalBounds().width / 2, 0);
    m_pauseTitle.setPosition(m_context->window->getSize().x / 2, m_pauseTitle.getPosition().y / 2);


    m_resumeButton.setFont( m_context->resources->GetFont("mainFont"));
    m_resumeButton.setString("Resume");
    m_resumeButton.setCharacterSize(40);
    m_resumeButton.setOutlineColor(sf::Color::Black);
    m_resumeButton.setOutlineThickness(3.0f);
    m_resumeButton.setOrigin(m_resumeButton.getLocalBounds().width / 2, 0);
    m_resumeButton.setPosition(m_pauseTitle.getPosition().x, m_pauseTitle.getPosition().y + (m_context->window->getSize().y / 4));


    m_exitButton.setFont( m_context->resources->GetFont("mainFont"));
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(40);
    m_exitButton.setOutlineColor(sf::Color::Black);
    m_exitButton.setOutlineThickness(3.0f);
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, 0);
    m_exitButton.setPosition(m_pauseTitle.getPosition().x, m_resumeButton.getPosition().y + 100);
}

void PauseMenu::ProccesInput()
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
            switch (event.key.code)
            {
                case sf::Keyboard::Up:
                {
                    if(false == m_isResumeButtonSelected)
                    {
                        m_isResumeButtonSelected = true;
                        m_isExitButtonSelected = false;
                    }
                    break;
                }
                case sf::Keyboard::Down:
                {
                    if(false == m_isExitButtonSelected)
                    {
                        m_isExitButtonSelected = true;
                        m_isResumeButtonSelected = false;
                    }
                    break;
                }
                case sf::Keyboard::Return:
                {
                    m_isResumeButtonPressed = false;
                    m_isExitButtonPressed = false;

                    if(m_isResumeButtonSelected)
                    {
                        m_isResumeButtonPressed = true;
                    }
                    else if(m_isExitButtonSelected)
                    {
                        m_isExitButtonPressed = true;
                    }

                    break;
                }
                case sf::Keyboard::Escape:
                {
                    m_isResumeButtonPressed = true;
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

void PauseMenu::Update(sf::Time deltaTime)
{
    sf::Color selectedColor = sf::Color::Yellow;
    if(m_isResumeButtonSelected)
    {
        m_resumeButton.setFillColor(selectedColor);
        m_exitButton.setFillColor(sf::Color::White);
    }
    if(m_isExitButtonSelected)
    {
        m_exitButton.setFillColor(selectedColor);
        m_resumeButton.setFillColor(sf::Color::White);
    }

    if(m_isResumeButtonPressed)
    {
        m_context->states->PopCurrentState();
    }
    if(m_isExitButtonPressed)
    {
         m_context->window->close();
    }
}

void PauseMenu::Draw()
{
    m_context->window->draw(m_pauseTitle);
    m_context->window->draw(m_resumeButton);
    m_context->window->draw(m_exitButton);
    m_context->window->display();
}
