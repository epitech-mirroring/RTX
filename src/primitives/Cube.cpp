/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Cube.hpp"

#include <utility>

Cube::Cube()
{
    _properties = cubeProperties();
}

Cube::Cube(const Material& material, const Transform& transform, std::vector<GLSL::Vertex> vertices, std::vector<std::size_t> indices, std::vector<Texture> textures, std::size_t size) : Object(material, transform, std::move(vertices), std::move(indices), std::move(textures))
{
    _properties.setSize(size);
}

Cube::Cube(const Material& material, const Transform& transform, std::vector<GLSL::Vertex> vertices, std::vector<std::size_t> indices, std::vector<Texture> textures, cubeProperties properties) : Object(material, transform, std::move(vertices), std::move(indices), std::move(textures))
{
    _properties = properties;
}

Cube::Cube(const Cube &other)
 : Object(other) {
    _properties = other._properties;
}

Cube::Cube(JsonObject *obj) : Object(obj)
{
    _properties = cubeProperties(obj->getValue<JsonObject>("properties"));
}

abstractProperties Cube::getProperties() const {
    return _properties;
}

cubeProperties &Cube::getProperties()
{
    return _properties;
}
