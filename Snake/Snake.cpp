#include "Snake.h"
#include "../ResourceManager/ResourceManager.h"

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

void Snake::Grow(const sf::Vector2f& direction)
{
    sf::Sprite newBodyPiece;
    newBodyPiece.setTexture(*m_body.begin()->getTexture());
    newBodyPiece.setPosition(m_head->getPosition() + direction);

    m_head = m_body.insert(++m_head, newBodyPiece);
}

bool Snake::isColliding(const sf::Sprite& other) const
{
    return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}

bool Snake::isSelfColliding() const
{
    for (auto bodyPiece = m_body.begin(); bodyPiece != m_body.end(); ++bodyPiece)
    {
        if(m_head != bodyPiece)
        {
            return isColliding(*bodyPiece);
        }
    }
    return false;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& bodyPiece : m_body)
    {
        target.draw(bodyPiece);
    }
}
