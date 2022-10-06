#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <unordered_map>

namespace Core
{

class ResourceManager
{
public:
    using Key = std::string;

    void LoadResource(const Key& key, const std::string& path);

    auto GetTexture(const Key& key) -> sf::Texture&;
    auto GetFont(const Key& key) const -> const sf::Font&;

private:
    std::unordered_map<Key, sf::Texture> m_textures;
    std::unordered_map<Key, sf::Font> m_fonts;
};

} // Core
