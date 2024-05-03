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
    _properties = CubeProperties();
}

Cube::Cube(const Material& material, const Transform& transform, const std::vector<Texture>& textures, std::size_t size) : Object(material, transform, std::vector<glm::vec3>(), std::vector<unsigned int>(), textures)
{
    _properties.setSize(size);
}

Cube::Cube(const Material& material, const Transform& transform, const std::vector<Texture>& textures, const CubeProperties& properties) : Object(material, transform, std::vector<glm::vec3>(), std::vector<unsigned int>(), textures)
{
    _properties = properties;
}

Cube::Cube(const Cube &other)
 : Object(other) {
    _properties = other._properties;
}

Cube::Cube(JsonObject *obj)
{
    _properties = CubeProperties(obj);
}

Cube::Cube(CubeProperties &properties): Object(properties)
{
    _properties = properties;
}

CubeProperties Cube::getProperties() const {
    return _properties;
}

CubeProperties &Cube::getProperties()
{
    return _properties;
}
