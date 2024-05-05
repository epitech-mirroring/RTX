/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Rectangle.hpp"
#include <utility>
#include <iostream>

static std::vector<Triangle> generateTriangles(const RectangleProperties &properties)
{
    float offsetX = (float) properties.getLength() / 2.f;
    float offsetY = (float) properties.getHeight() / 2.f;
    float offsetZ = (float) properties.getWidth() / 2.f;
    std::vector<Triangle> triangles;
    Triangle triangle{};

    //front
    triangle.v0 = glm::vec3(offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(-offsetX, offsetY, -offsetZ);
    triangle.v2 = glm::vec3(offsetX, offsetY, -offsetZ);
    triangle.normalV0 = {0, 0, -1};
    triangle.normalV1 = {0, 0, -1};
    triangle.normalV2 = {0, 0, -1};
    triangles.push_back(triangle);

    triangle.v0 = glm::vec3(-offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(-offsetX, offsetY, -offsetZ);
    triangle.v2 = glm::vec3(offsetX, -offsetY, -offsetZ);
    triangle.normalV0 = {0, 0, -1};
    triangle.normalV1 = {0, 0, -1};
    triangle.normalV2 = {0, 0, -1};
    triangles.push_back(triangle);

    //right
    triangle.v0 = glm::vec3(offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(offsetX, offsetY, -offsetZ);
    triangle.v2 = glm::vec3(offsetX, offsetY, offsetZ);
    triangle.normalV0 = {1, 0, 0};
    triangle.normalV1 = {1, 0, 0};
    triangle.normalV2 = {1, 0, 0};
    triangles.push_back(triangle);

    triangle.v0 = glm::vec3(offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(offsetX, offsetY, offsetZ);
    triangle.v2 = glm::vec3(offsetX, -offsetY, offsetZ);
    triangle.normalV0 = {1, 0, 0};
    triangle.normalV1 = {1, 0, 0};
    triangle.normalV2 = {1, 0, 0};
    triangles.push_back(triangle);

    //back
    triangle.v0 = glm::vec3(offsetX, -offsetY, offsetZ);
    triangle.v1 = glm::vec3(-offsetX, -offsetY, offsetZ);
    triangle.v2 = glm::vec3(offsetX, offsetY, offsetZ);
    triangle.normalV0 = {0, 0, 1};
    triangle.normalV1 = {0, 0, 1};
    triangle.normalV2 = {0, 0, 1};
    triangles.push_back(triangle);

    triangle.v0 = glm::vec3(-offsetX, -offsetY, offsetZ);
    triangle.v1 = glm::vec3(offsetX, offsetY, offsetZ);
    triangle.v2 = glm::vec3(-offsetX, offsetY, offsetZ);
    triangle.normalV0 = {0, 0, 1};
    triangle.normalV1 = {0, 0, 1};
    triangle.normalV2 = {0, 0, 1};
    triangles.push_back(triangle);

    //left
    triangle.v0 = glm::vec3(offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(-offsetX, -offsetY, -offsetZ);
    triangle.v2 = glm::vec3(offsetX, -offsetY, offsetZ);
    triangle.normalV0 = {-1, 0, 0};
    triangle.normalV1 = {-1, 0, 0};
    triangle.normalV2 = {-1, 0, 0};
    triangles.push_back(triangle);

    triangle.v0 = glm::vec3(-offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(-offsetX, -offsetY, offsetZ);
    triangle.v2 = glm::vec3(offsetX, -offsetY, offsetZ);
    triangle.normalV0 = {-1, 0, 0};
    triangle.normalV1 = {-1, 0, 0};
    triangle.normalV2 = {-1, 0, 0};
    triangles.push_back(triangle);

    //top
    triangle.v0 = glm::vec3(offsetX, offsetY, -offsetZ);
    triangle.v1 = glm::vec3(-offsetX, offsetY, -offsetZ);
    triangle.v2 = glm::vec3(offsetX, offsetY, offsetZ);
    triangle.normalV0 = {0, 1, 0};
    triangle.normalV1 = {0, 1, 0};
    triangle.normalV2 = {0, 1, 0};
    triangles.push_back(triangle);

    triangle.v0 = glm::vec3(-offsetX, offsetY, -offsetZ);
    triangle.v1 = glm::vec3(offsetX, offsetY, offsetZ);
    triangle.v2 = glm::vec3(-offsetX, offsetY, offsetZ);
    triangle.normalV0 = {0, 1, 0};
    triangle.normalV1 = {0, 1, 0};
    triangle.normalV2 = {0, 1, 0};
    triangles.push_back(triangle);

    //bottom
    triangle.v0 = glm::vec3(offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(offsetX, -offsetY, offsetZ);
    triangle.v2 = glm::vec3(-offsetX, -offsetY, offsetZ);
    triangle.normalV0 = {0, 1, 0};
    triangle.normalV1 = {0, 1, 0};
    triangle.normalV2 = {0, 1, 0};
    triangles.emplace_back(triangle);

    triangle.v0 = glm::vec3(-offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(-offsetX, -offsetY, offsetZ);
    triangle.v2 = glm::vec3(offsetX, -offsetY, offsetZ);
    triangle.normalV0 = {0, -1, 0};
    triangle.normalV1 = {0, -1, 0};
    triangle.normalV2 = {0, -1, 0};
    triangles.push_back(triangle);

    return triangles;
}

Rectangle::Rectangle()
{
    _properties = RectangleProperties();
}

Rectangle::Rectangle(const Material& material, const Transform& transform, const std::vector<Texture>& textures, float length, float width, float height) : Object(material, transform, generateTriangles(RectangleProperties(length, width, height)), textures)
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
