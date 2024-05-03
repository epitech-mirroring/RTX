/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Sphere.hpp"
#include <cmath>
#include <iostream>

Sphere::Sphere()
{
    _properties = SphereProperties();
}

Sphere::Sphere(const Material& material, const Transform& transform, const std::vector<Texture>& textures, std::size_t radius) : Object(material, transform, std::vector<glm::vec3>(), std::vector<unsigned int>(), textures)
{
    _properties.setRadius(radius);
}

Sphere::Sphere(const Material& material, const Transform& transform, const std::vector<Texture>& textures, const SphereProperties& properties) : Object(material, transform, Sphere::generateVertices(properties), Sphere::generateIndices(properties), textures)
{
    _properties = properties;
}

Sphere::Sphere(const Sphere &other)  : Object(other) {
    _properties = other._properties;
}

Sphere::Sphere(JsonObject *obj)
{
    _properties = SphereProperties(obj);
}

Sphere::Sphere(SphereProperties &properties): Object(properties)
{
    _properties = properties;
    _vertices = Sphere::generateVertices(properties);
    _indices = Sphere::generateIndices(properties);
}

SphereProperties Sphere::getProperties() const {
    return _properties;
}

SphereProperties &Sphere::getProperties()
{
    return _properties;
}

void Sphere::setProperties(const SphereProperties &properties)
{
    _properties = properties;
}

std::vector<glm::vec3> Sphere::generateVertices(const SphereProperties &properties) {
    std::vector<glm::vec3> vertices;
    double phi = 1.618;

    vertices.emplace_back(properties.getTransform().getPosition().x, properties.getTransform().getPosition().y + (double)properties.getRadius(), properties.getTransform().getPosition().z);
    vertices.emplace_back(properties.getTransform().getPosition().x, properties.getTransform().getPosition().y - (double)properties.getRadius(), properties.getTransform().getPosition().z);
    vertices.emplace_back(properties.getTransform().getPosition().x, properties.getTransform().getPosition().y, properties.getTransform().getPosition().z + (double)properties.getRadius());
    vertices.emplace_back(properties.getTransform().getPosition().x, properties.getTransform().getPosition().y, properties.getTransform().getPosition().z - (double)properties.getRadius());

    vertices.emplace_back(properties.getTransform().getPosition().x + (double)properties.getRadius(), properties.getTransform().getPosition().y, properties.getTransform().getPosition().z + ((double)properties.getRadius()) * phi);
    vertices.emplace_back(properties.getTransform().getPosition().x - (double)properties.getRadius(), properties.getTransform().getPosition().y, properties.getTransform().getPosition().z + ((double)properties.getRadius()) * phi);
    vertices.emplace_back(properties.getTransform().getPosition().x + (double)properties.getRadius(), properties.getTransform().getPosition().y, properties.getTransform().getPosition().z - ((double)properties.getRadius()) * phi);
    vertices.emplace_back(properties.getTransform().getPosition().x - (double)properties.getRadius(), properties.getTransform().getPosition().y, properties.getTransform().getPosition().z - ((double)properties.getRadius()) * phi);

    vertices.emplace_back(properties.getTransform().getPosition().x + ((double)properties.getRadius() * phi), properties.getTransform().getPosition().y + (double)properties.getRadius(), properties.getTransform().getPosition().z);
    vertices.emplace_back(properties.getTransform().getPosition().x + ((double)properties.getRadius() * phi), properties.getTransform().getPosition().y - (double)properties.getRadius(), properties.getTransform().getPosition().z);
    vertices.emplace_back(properties.getTransform().getPosition().x - ((double)properties.getRadius() * phi), properties.getTransform().getPosition().y + (double)properties.getRadius(), properties.getTransform().getPosition().z);
    vertices.emplace_back(properties.getTransform().getPosition().x - ((double)properties.getRadius() * phi), properties.getTransform().getPosition().y - (double)properties.getRadius(), properties.getTransform().getPosition().z);

    return vertices;
}

std::vector<unsigned int> Sphere::generateIndices(const SphereProperties &properties) {
    std::vector<unsigned int> indices;

    return indices;
}
