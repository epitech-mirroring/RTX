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

Rectangle::Rectangle(const Material& material, const Transform& transform, const std::vector<Texture>& textures, std::size_t length, std::size_t width, std::size_t height) : Object(material, transform, Rectangle::generateVertices(RectangleProperties(length, width, height)), Rectangle::generateIndices(), textures)
{
    _properties = RectangleProperties(length, width, height);
}

Rectangle::Rectangle(const Material& material, const Transform& transform, const std::vector<Texture>& textures, const RectangleProperties & properties) : Object(material, transform, Rectangle::generateVertices(properties), Rectangle::generateIndices(), textures)
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

std::vector<glm::vec3> Rectangle::generateVertices(const RectangleProperties &properties)
{
    std::vector<glm::vec3> vertices;
    glm::vec3 position = properties.getTransform().getPosition();

    //102
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);

    //302
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);

    //651
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);

    //251
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);

    //764
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);

    //564
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);

    //037
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);

    //437
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);

    //235
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);

    //435
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);

    //160
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);

    //760
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    vertices.emplace_back((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);

    return vertices;
}

std::vector<unsigned int> Rectangle::generateIndices()
{
    std::vector<unsigned int> indices;

    indices.push_back(1);
    indices.push_back(0);
    indices.push_back(2);

    indices.push_back(3);
    indices.push_back(0);
    indices.push_back(2);

    indices.push_back(6);
    indices.push_back(5);
    indices.push_back(1);

    indices.push_back(2);
    indices.push_back(5);
    indices.push_back(1);

    indices.push_back(7);
    indices.push_back(6);
    indices.push_back(4);

    indices.push_back(5);
    indices.push_back(6);
    indices.push_back(4);

    indices.push_back(0);
    indices.push_back(3);
    indices.push_back(7);

    indices.push_back(4);
    indices.push_back(3);
    indices.push_back(7);

    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(5);

    indices.push_back(4);
    indices.push_back(3);
    indices.push_back(5);

    indices.push_back(1);
    indices.push_back(6);
    indices.push_back(0);

    indices.push_back(7);
    indices.push_back(6);
    indices.push_back(0);
    return indices;
}
