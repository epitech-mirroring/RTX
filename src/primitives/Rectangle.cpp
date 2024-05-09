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
    std::vector<Triangle> triangles = {
            // Front
            {{-offsetX, -offsetY, -offsetZ}, {-offsetX, offsetY, -offsetZ}, {offsetX, offsetY, -offsetZ}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}},
            {{-offsetX, -offsetY, -offsetZ}, {offsetX, offsetY, -offsetZ}, {offsetX, -offsetY, -offsetZ}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}},
            // Back
            {{-offsetX, -offsetY, offsetZ}, {offsetX, -offsetY, offsetZ}, {offsetX, offsetY, offsetZ}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}},
            {{-offsetX, -offsetY, offsetZ}, {offsetX, offsetY, offsetZ}, {-offsetX, offsetY, offsetZ}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}},
            // Left
            {{-offsetX, -offsetY, -offsetZ}, {-offsetX, -offsetY, offsetZ}, {-offsetX, offsetY, offsetZ}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}},
            {{-offsetX, -offsetY, -offsetZ}, {-offsetX, offsetY, offsetZ}, {-offsetX, offsetY, -offsetZ}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}},
            // Right
            {{offsetX, -offsetY, -offsetZ}, {offsetX, offsetY, -offsetZ}, {offsetX, offsetY, offsetZ}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}},
            {{offsetX, -offsetY, -offsetZ}, {offsetX, offsetY, offsetZ}, {offsetX, -offsetY, offsetZ}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}},
            // Top
            {{-offsetX, offsetY, -offsetZ}, {-offsetX, offsetY, offsetZ}, {offsetX, offsetY, offsetZ}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}},
            {{-offsetX, offsetY, -offsetZ}, {offsetX, offsetY, offsetZ}, {offsetX, offsetY, -offsetZ}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}},
            // Bottom
            {{-offsetX, -offsetY, -offsetZ}, {offsetX, -offsetY, -offsetZ}, {offsetX, -offsetY, offsetZ}, {0, -1, 0}, {0, -1, 0}, {0, -1, 0}},
            {{-offsetX, -offsetY, -offsetZ}, {offsetX, -offsetY, offsetZ}, {-offsetX, -offsetY, offsetZ}, {0, -1, 0}, {0, -1, 0}, {0, -1, 0}},
    };

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
