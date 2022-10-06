#include "MainMenu.h"

#include "../GamePlay/GamePlay.h"

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context>& context) : m_context(context)
{

}

void MainMenu::Init()
{
    m_context->resources->LoadResource("mainFont","/home/default/projects/SnakeGame/assets/fonts/Pacifico-Regular.ttf");

    m_gameTitle.setFont( m_context->resources->GetFont("mainFont"));
    m_gameTitle.setString("Snake Game");
    m_gameTitle.setCharacterSize(60);
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, 0);
    m_gameTitle.setPosition(m_context->window->getSize().x / 2, m_gameTitle.getPosition().y / 2);


    m_playButton.setFont( m_context->resources->GetFont("mainFont"));
    m_playButton.setString("Play");
    m_playButton.setCharacterSize(40);
    m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2, 0);
    m_playButton.setPosition(m_gameTitle.getPosition().x, m_gameTitle.getPosition().y + (m_context->window->getSize().y / 4));


    m_exitButton.setFont( m_context->resources->GetFont("mainFont"));
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(40);
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, 0);
    m_exitButton.setPosition(m_gameTitle.getPosition().x, m_playButton.getPosition().y + 100);
}

void MainMenu::ProccesInput()
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
                    if(false == m_isPlayButtonSelected)
                    {
                        m_isPlayButtonSelected = true;
                        m_isExitButtonSelected = false;
                    }
                    break;
                }
                case sf::Keyboard::Down:
                {
                    if(false == m_isExitButtonSelected)
                    {
                        m_isExitButtonSelected = true;
                        m_isPlayButtonSelected = false;
                    }
                    break;
                }
                case sf::Keyboard::Return:
                {
                    m_isPlayButtonPressed = false;
                    m_isExitButtonPressed = false;

                    if(m_isPlayButtonSelected)
                    {
                        m_isPlayButtonPressed = true;
                    }
                    else if(m_isExitButtonSelected)
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

void MainMenu::Update(sf::Time deltaTime)
{
    sf::Color selectedColor = sf::Color::Yellow;
    if(m_isPlayButtonSelected)
    {
        m_playButton.setFillColor(selectedColor);
        m_exitButton.setFillColor(sf::Color::White);
    }
    if(m_isExitButtonSelected)
    {
        m_exitButton.setFillColor(selectedColor);
        m_playButton.setFillColor(sf::Color::White);
    }

    if(m_isPlayButtonPressed)
    {
        m_context->states->AddState(std::make_unique<GamePlay>(m_context));
    }
    if(m_isExitButtonPressed)
    {
         m_context->window->close();
    }
}

void MainMenu::Draw()
{
    m_context->window->clear(sf::Color::Blue);
    m_context->window->draw(m_gameTitle);
    m_context->window->draw(m_playButton);
    m_context->window->draw(m_exitButton);
    m_context->window->display();
}
