#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <list>

class Snake : public sf::Drawable
{
public:
    Snake();

    void Init(const sf::Texture& texture);
    void Move(const sf::Vector2f& direction);
    void Draw(const sf::Vector2f& direction);

    bool isColliding(const sf::Sprite& other) const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    std::list<sf::Sprite> m_body;
    std::list<sf::Sprite>::iterator m_head;
    std::list<sf::Sprite>::iterator m_tail;
};
