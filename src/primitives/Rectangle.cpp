/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Rectangle.hpp"
#include <utility>

Rectangle::Rectangle()
{
    _properties = RectangleProperties();
}

Rectangle::Rectangle(const Material& material, const Transform& transform, const std::vector<Texture>& textures, std::size_t length, std::size_t width, std::size_t height) : Object(material, transform, std::vector<glm::vec3>(), std::vector<unsigned int>(), textures)
{
    _properties = RectangleProperties(length, width, height);
}

Rectangle::Rectangle(const Material& material, const Transform& transform, const std::vector<Texture>& textures, const RectangleProperties & properties) : Object(material, transform, std::vector<glm::vec3>(), std::vector<unsigned int>(), textures)
{
    _properties = properties;
}

Rectangle::Rectangle(const Rectangle &other)
 : Object(other) {
    _properties = other._properties;
}

Rectangle::Rectangle(JsonObject *obj)
{
    _properties = RectangleProperties(obj);
}

Rectangle::Rectangle(RectangleProperties &properties): Object(properties)
{
    _properties = properties;
}

RectangleProperties Rectangle::getProperties() const {
    return _properties;
}

RectangleProperties &Rectangle::getProperties()
{
    return _properties;
}
