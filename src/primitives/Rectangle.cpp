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

static std::vector<Triangle> generateTriangles(float length, float width, float height)
{
    float offsetX = length / 2.f;
    float offsetY = height / 2.f;
    float offsetZ = width / 2.f;
    std::vector<Triangle> triangles;
    Triangle triangle{};

    //front
    triangle.v0 = glm::vec3(offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(-offsetX, offsetY, -offsetZ);
    triangle.v2 = glm::vec3(offsetX, offsetY, -offsetZ);
    triangle.normalV0 = {0.0f, 0.0f, -1.0f};
    triangle.normalV1 = {0.0f, 0.0f, -1.0f};
    triangle.normalV2 = {0.0f, 0.0f, -1.0f};
    triangles.push_back(triangle);

    triangle.v0 = glm::vec3(-offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(-offsetX, offsetY, -offsetZ);
    triangle.v2 = glm::vec3(offsetX, -offsetY, -offsetZ);
    triangle.normalV0 = {0.0f, 0.0f, -1.0f};
    triangle.normalV1 = {0.0f, 0.0f, -1.0f};
    triangle.normalV2 = {0.0f, 0.0f, -1.0f};
    triangles.push_back(triangle);

    //right
    triangle.v0 = glm::vec3(offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(offsetX, offsetY, -offsetZ);
    triangle.v2 = glm::vec3(offsetX, offsetY, offsetZ);
    triangle.normalV0 = {1.0f, 0.0f, 0.0f};
    triangle.normalV1 = {1.0f, 0.0f, 0.0f};
    triangle.normalV2 = {1.0f, 0.0f, 0.0f};
    triangles.push_back(triangle);

    triangle.v0 = glm::vec3(offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(offsetX, offsetY, offsetZ);
    triangle.v2 = glm::vec3(offsetX, -offsetY, offsetZ);
    triangle.normalV0 = {1.0f, 0.0f, 0.0f};
    triangle.normalV1 = {1.0f, 0.0f, 0.0f};
    triangle.normalV2 = {1.0f, 0.0f, 0.0f};
    triangles.push_back(triangle);

    //back
    triangle.v0 = glm::vec3(offsetX, -offsetY, offsetZ);
    triangle.v1 = glm::vec3(-offsetX, -offsetY, offsetZ);
    triangle.v2 = glm::vec3(offsetX, offsetY, offsetZ);
    triangle.normalV0 = {0.0f, 0.0f, 1.0f};
    triangle.normalV1 = {0.0f, 0.0f, 1.0f};
    triangle.normalV2 = {0.0f, 0.0f, 1.0f};
    triangles.push_back(triangle);

    triangle.v0 = glm::vec3(-offsetX, -offsetY, offsetZ);
    triangle.v1 = glm::vec3(offsetX, offsetY, offsetZ);
    triangle.v2 = glm::vec3(-offsetX, offsetY, offsetZ);
    triangle.normalV0 = {0.0f, 0.0f, 1.0f};
    triangle.normalV1 = {0.0f, 0.0f, 1.0f};
    triangle.normalV2 = {0.0f, 0.0f, 1.0f};
    triangles.push_back(triangle);

    //left
    triangle.v0 = glm::vec3(offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(-offsetX, -offsetY, -offsetZ);
    triangle.v2 = glm::vec3(offsetX, -offsetY, offsetZ);
    triangle.normalV0 = {-1.0f, 0.0f, 0.0f};
    triangle.normalV1 = {-1.0f, 0.0f, 0.0f};
    triangle.normalV2 = {-1.0f, 0.0f, 0.0f};
    triangles.push_back(triangle);

    triangle.v0 = glm::vec3(-offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(-offsetX, -offsetY, offsetZ);
    triangle.v2 = glm::vec3(offsetX, -offsetY, offsetZ);
    triangle.normalV0 = {-1.0f, 0.0f, 0.0f};
    triangle.normalV1 = {-1.0f, 0.0f, 0.0f};
    triangle.normalV2 = {-1.0f, 0.0f, 0.0f};
    triangles.push_back(triangle);

    //top
    triangle.v0 = glm::vec3(offsetX, offsetY, -offsetZ);
    triangle.v1 = glm::vec3(-offsetX, offsetY, -offsetZ);
    triangle.v2 = glm::vec3(offsetX, offsetY, offsetZ);
    triangle.normalV0 = {0.0f, 1.0f, 0.0f};
    triangle.normalV1 = {0.0f, 1.0f, 0.0f};
    triangle.normalV2 = {0.0f, 1.0f, 0.0f};
    triangles.push_back(triangle);

    triangle.v0 = glm::vec3(-offsetX, offsetY, -offsetZ);
    triangle.v1 = glm::vec3(offsetX, offsetY, offsetZ);
    triangle.v2 = glm::vec3(-offsetX, offsetY, offsetZ);
    triangle.normalV0 = {0.0f, 1.0f, 0.0f};
    triangle.normalV1 = {0.0f, 1.0f, 0.0f};
    triangle.normalV2 = {0.0f, 1.0f, 0.0f};
    triangles.push_back(triangle);

    //bottom
    triangle.v0 = glm::vec3(offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(offsetX, -offsetY, offsetZ);
    triangle.v2 = glm::vec3(-offsetX, -offsetY, offsetZ);
    triangle.normalV0 = {0.0f, 1.0f, 0.0f};
    triangle.normalV1 = {0.0f, 1.0f, 0.0f};
    triangle.normalV2 = {0.0f, 1.0f, 0.0f};
    triangles.emplace_back(triangle);

    triangle.v0 = glm::vec3(-offsetX, -offsetY, -offsetZ);
    triangle.v1 = glm::vec3(-offsetX, -offsetY, offsetZ);
    triangle.v2 = glm::vec3(offsetX, -offsetY, offsetZ);
    triangle.normalV0 = {0.0f, -1.0f, 0.0f};
    triangle.normalV1 = {0.0f, -1.0f, 0.0f};
    triangle.normalV2 = {0.0f, -1.0f, 0.0f};
    triangles.push_back(triangle);

    return triangles;
}

Rectangle::Rectangle()
{
    _properties = RectangleProperties();
}

Rectangle::Rectangle(const Material& material, const Transform& transform, const std::vector<Texture>& textures, float length, float width, float height) : Object(material, transform, generateTriangles(length, width, height), textures)
{
    _properties = RectangleProperties(length, width, height);
}

Rectangle::Rectangle(const Material& material, const Transform& transform, const std::vector<Texture>& textures, const RectangleProperties & properties) : Object(material, transform, generateTriangles(properties.getLength(), properties.getWidth(), properties.getHeight()), textures)
{
    _properties = properties;
}

Rectangle::Rectangle(const Rectangle &other) : Object(other)
{
    _properties = other._properties;
}

Rectangle::Rectangle(JsonObject *obj)
{
    _properties = RectangleProperties(obj);
    _triangles = generateTriangles(_properties.getLength(), _properties.getWidth(), _properties.getHeight());
}

Rectangle::Rectangle(RectangleProperties &properties) : Object(properties)
{
    _properties = properties;
    _triangles = generateTriangles(properties.getLength(), properties.getWidth(), properties.getHeight());
}

RectangleProperties Rectangle::getProperties() const
{
    return _properties;
}

RectangleProperties &Rectangle::getProperties()
{
    return _properties;
}
