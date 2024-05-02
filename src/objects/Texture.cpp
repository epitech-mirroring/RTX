/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Texture.hpp"

Texture::Texture()
{
    _path = "";
    _type = NORMAL;
}

Texture::Texture(const Texture &texture)
{
    _path = texture._path;
    _type = texture._type;
}

Texture::Texture(const std::string &path, const TextureType type)
{
    _path = path;
    _type = type;
}

Texture::Texture(JsonObject *obj)
{
    std::string type = obj->getString("type");

    this->_path = obj->getString("path");
    if (type == "diffuse")
        this->_type = Texture::TextureType::DIFFUSE;
    else if (type == "specular")
        this->_type = Texture::TextureType::SPECULAR;
    else if (type == "normal")
        this->_type = Texture::TextureType::NORMAL;
    else if (type == "height")
        this->_type = Texture::TextureType::HEIGHT;
    else {
        throw std::invalid_argument("Error: Invalid texture type");
    }
}

void Texture::setPath(const std::string &path)
{
    _path = path;
}

void Texture::setType(const TextureType type)
{
    _type = type;
}

std::string Texture::getPath() const
{
    return _path;
}

Texture::TextureType Texture::getType() const
{
    return _type;
}

std::string &Texture::getPath()
{
    return _path;
}

Texture::TextureType &Texture::getType()
{
    return _type;
}
