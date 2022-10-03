#include "ResourceManager.h"
#include <iostream>

#include <unistd.h>
#include <stdio.h>
#include <limits.h>

namespace Core
{

void ResourceManager::LoadResource(const ResourceManager::Key &key, const std::string &path)
{
    auto pathExtension = path.substr(path.size() - 4);

    if(pathExtension == ".ttf")
    {
        m_fonts[key].loadFromFile(path);
        return;
    }
    else if(pathExtension == ".png")
    {
        m_textures[key].loadFromFile(path);
        return;
    }

    std::cout << "File not found." << std::endl;
}

auto ResourceManager::GetTexture(const ResourceManager::Key &key) const -> const sf::Texture&
{
    auto iter = m_textures.find(key);
    if(iter != m_textures.end())
    {
        return iter->second;
    }

    static sf::Texture empty;
    return empty;
}

auto ResourceManager::GetFont(const ResourceManager::Key &key) const -> const sf::Font&
{
    auto iter = m_fonts.find(key);
    if(iter != m_fonts.end())
    {
        return iter->second;
    }

    static sf::Font empty;
    return empty;
}

} // Core
