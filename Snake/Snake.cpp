#include "Snake.h"

Snake::Snake() : m_body(std::list<sf::Sprite>(4))
{
    m_head = --m_body.end();
    m_tail = m_body.begin();
}

void Snake::Init(const sf::Texture& texture)
{
    float xPos = 16.0f;
    for (auto& bodyPiece : m_body)
    {
        bodyPiece.setTexture(texture);
        bodyPiece.setPosition({xPos, 16.0f});
        xPos += 16.0f;
    }
}

void Snake::Move(const sf::Vector2f& direction)
{
    m_tail->setPosition(m_head->getPosition() + direction);
    m_head = m_tail;
    m_tail++;

    if(m_tail == m_body.end())
    {
        m_tail = m_body.begin();
    }
}

void Snake::Draw(const sf::Vector2f& direction)
{

}

bool Snake::isColliding(const sf::Sprite& other) const
{

}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& bodyPiece : m_body)
    {
        target.draw(bodyPiece);
    }
}
