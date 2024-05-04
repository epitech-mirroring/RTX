/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Rectangle.hpp"
#include <utility>


static std::vector<Triangle> generateTriangles(const RectangleProperties &properties)
{
    std::vector<Triangle> triangles = std::vector<Triangle>();
    glm::vec3 position = properties.getTransform().getPosition();
    Triangle triangle{};

    //102
    triangle.v0 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.v1 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.v2 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.normalV0 = triangle.v0 * triangle.v1;
    triangle.normalV1 = triangle.v1 * triangle.v2;
    triangle.normalV2 = triangle.v2 * triangle.v0;
    triangles.push_back(triangle);

    //302
    triangle.v0 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.v1 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.v2 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.normalV0 = triangle.v0 * triangle.v1;
    triangle.normalV1 = triangle.v1 * triangle.v2;
    triangle.normalV2 = triangle.v2 * triangle.v0;
    triangles.push_back(triangle);

    //651
    triangle.v0 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.v1 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.v2 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.normalV0 = triangle.v0 * triangle.v1;
    triangle.normalV1 = triangle.v1 * triangle.v2;
    triangle.normalV2 = triangle.v2 * triangle.v0;
    triangles.push_back(triangle);

    //251
    triangle.v0 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.v1 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.v2 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.normalV0 = triangle.v0 * triangle.v1;
    triangle.normalV1 = triangle.v1 * triangle.v2;
    triangle.normalV2 = triangle.v2 * triangle.v0;
    triangles.push_back(triangle);

    //764
    triangle.v0 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.v1 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.v2 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.normalV0 = triangle.v0 * triangle.v1;
    triangle.normalV1 = triangle.v1 * triangle.v2;
    triangle.normalV2 = triangle.v2 * triangle.v0;
    triangles.push_back(triangle);

    //564
    triangle.v0 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.v1 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.v2 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.normalV0 = triangle.v0 * triangle.v1;
    triangle.normalV1 = triangle.v1 * triangle.v2;
    triangle.normalV2 = triangle.v2 * triangle.v0;
    triangles.push_back(triangle);

    //037
    triangle.v0 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.v1 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.v2 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.normalV0 = triangle.v0 * triangle.v1;
    triangle.normalV1 = triangle.v1 * triangle.v2;
    triangle.normalV2 = triangle.v2 * triangle.v0;
    triangles.push_back(triangle);

    //437
    triangle.v0 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.v1 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.v2 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.normalV0 = triangle.v0 * triangle.v1;
    triangle.normalV1 = triangle.v1 * triangle.v2;
    triangle.normalV2 = triangle.v2 * triangle.v0;
    triangles.push_back(triangle);

    //235
    triangle.v0 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.v1 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.v2 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.normalV0 = triangle.v0 * triangle.v1;
    triangle.normalV1 = triangle.v1 * triangle.v2;
    triangle.normalV2 = triangle.v2 * triangle.v0;
    triangles.push_back(triangle);

    //435
    triangle.v0 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.v1 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.v2 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y + properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.normalV0 = triangle.v0 * triangle.v1;
    triangle.normalV1 = triangle.v1 * triangle.v2;
    triangle.normalV2 = triangle.v2 * triangle.v0;
    triangles.push_back(triangle);

    //160
    triangle.v0 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.v1 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.v2 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.normalV0 = triangle.v0 * triangle.v1;
    triangle.normalV1 = triangle.v1 * triangle.v2;
    triangle.normalV2 = triangle.v2 * triangle.v0;
    triangles.push_back(triangle);

    //760
    triangle.v0 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.v1 = glm::vec3((std::size_t)position.x + properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z + properties.getWidth() / 2);
    triangle.v2 = glm::vec3((std::size_t)position.x - properties.getLength() / 2, (std::size_t)position.y - properties.getHeight() / 2, (std::size_t)position.z - properties.getWidth() / 2);
    triangle.normalV0 = triangle.v0 * triangle.v1;
    triangle.normalV1 = triangle.v1 * triangle.v2;
    triangle.normalV2 = triangle.v2 * triangle.v0;
    triangles.push_back(triangle);

    return triangles;
}

Rectangle::Rectangle()
{
    _properties = RectangleProperties();
}

Rectangle::Rectangle(const Material& material, const Transform& transform, const std::vector<Texture>& textures, std::size_t length, std::size_t width, std::size_t height) : Object(material, transform, generateTriangles(RectangleProperties(length, width, height)), textures)
{
    _properties = RectangleProperties(length, width, height);
}

Rectangle::Rectangle(const Material& material, const Transform& transform, const std::vector<Texture>& textures, const RectangleProperties & properties) : Object(material, transform, generateTriangles(properties), textures)
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
    _triangles = generateTriangles(_properties);
}

Rectangle::Rectangle(RectangleProperties &properties): Object(properties)
{
    _properties = properties;
    _triangles = generateTriangles(properties);
}

RectangleProperties Rectangle::getProperties() const {
    return _properties;
}

RectangleProperties &Rectangle::getProperties()
{
    return _properties;
}
