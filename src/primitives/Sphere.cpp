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

    std::vector<glm::vec3> triangles;

    triangles.emplace_back(vertices.at(0));
    triangles.emplace_back(vertices.at(1));
    triangles.emplace_back(vertices.at(2));

    triangles.emplace_back(vertices.at(0));
    triangles.emplace_back(vertices.at(2));
    triangles.emplace_back(vertices.at(3));

    triangles.emplace_back(vertices.at(0));
    triangles.emplace_back(vertices.at(3));
    triangles.emplace_back(vertices.at(4));

    triangles.emplace_back(vertices.at(0));
    triangles.emplace_back(vertices.at(4));
    triangles.emplace_back(vertices.at(5));

    triangles.emplace_back(vertices.at(0));
    triangles.emplace_back(vertices.at(5));
    triangles.emplace_back(vertices.at(1));

    triangles.emplace_back(vertices.at(1));
    triangles.emplace_back(vertices.at(6));
    triangles.emplace_back(vertices.at(2));

    triangles.emplace_back(vertices.at(2));
    triangles.emplace_back(vertices.at(7));
    triangles.emplace_back(vertices.at(3));

    triangles.emplace_back(vertices.at(3));
    triangles.emplace_back(vertices.at(8));
    triangles.emplace_back(vertices.at(4));

    triangles.emplace_back(vertices.at(4));
    triangles.emplace_back(vertices.at(9));
    triangles.emplace_back(vertices.at(5));

    triangles.emplace_back(vertices.at(5));
    triangles.emplace_back(vertices.at(10));
    triangles.emplace_back(vertices.at(1));

    triangles.emplace_back(vertices.at(6));
    triangles.emplace_back(vertices.at(2));
    triangles.emplace_back(vertices.at(7));

    triangles.emplace_back(vertices.at(7));
    triangles.emplace_back(vertices.at(3));
    triangles.emplace_back(vertices.at(8));

    triangles.emplace_back(vertices.at(8));
    triangles.emplace_back(vertices.at(4));
    triangles.emplace_back(vertices.at(9));

    triangles.emplace_back(vertices.at(9));
    triangles.emplace_back(vertices.at(5));
    triangles.emplace_back(vertices.at(10));

    triangles.emplace_back(vertices.at(10));
    triangles.emplace_back(vertices.at(1));
    triangles.emplace_back(vertices.at(6));

    triangles.emplace_back(vertices.at(11));
    triangles.emplace_back(vertices.at(6));
    triangles.emplace_back(vertices.at(7));

    triangles.emplace_back(vertices.at(11));
    triangles.emplace_back(vertices.at(7));
    triangles.emplace_back(vertices.at(8));

    triangles.emplace_back(vertices.at(11));
    triangles.emplace_back(vertices.at(8));
    triangles.emplace_back(vertices.at(9));

    triangles.emplace_back(vertices.at(11));
    triangles.emplace_back(vertices.at(9));
    triangles.emplace_back(vertices.at(10));

    triangles.emplace_back(vertices.at(11));
    triangles.emplace_back(vertices.at(10));
    triangles.emplace_back(vertices.at(6));

    return Sphere::duplicateTriangles(triangles);
}

std::vector<unsigned int> Sphere::generateIndices(const SphereProperties &properties) {
    std::vector<unsigned int> indices;

    return indices;
}

std::vector<glm::vec3> Sphere::duplicateTriangles(std::vector<glm::vec3>& vertex)
{
    std::vector<glm::vec3> triangles;
    std::vector<glm::vec3> newTriangle;

    for (std::size_t j = 0; j < 3; j++) {
        for (std::size_t i = 0; i < vertex.size(); i += 3) {
            newTriangle.clear();
            newTriangle.emplace_back(vertex.at(i));
            newTriangle.emplace_back(vertex.at(i + 1));
            newTriangle.emplace_back(vertex.at(i + 2));
            newTriangle.emplace_back(
                    (newTriangle.at(0).x + newTriangle.at(1).x) / 2,
                    (newTriangle.at(0).y + newTriangle.at(1).y) / 2,
                    (newTriangle.at(0).z + newTriangle.at(1).z / 2));
            newTriangle.emplace_back(
                    (newTriangle.at(0).x + newTriangle.at(2).x) / 2,
                    (newTriangle.at(0).y + newTriangle.at(2).y) / 2,
                    (newTriangle.at(0).z + newTriangle.at(2).z / 2));
            newTriangle.emplace_back(
                    (newTriangle.at(2).x + newTriangle.at(1).x) / 2,
                    (newTriangle.at(2).y + newTriangle.at(1).y) / 2,
                    (newTriangle.at(2).z + newTriangle.at(1).z / 2));

            triangles.emplace_back(newTriangle.at(0));
            triangles.emplace_back(newTriangle.at(3));
            triangles.emplace_back(newTriangle.at(4));

            triangles.emplace_back(newTriangle.at(3));
            triangles.emplace_back(newTriangle.at(1));
            triangles.emplace_back(newTriangle.at(5));

            triangles.emplace_back(newTriangle.at(4));
            triangles.emplace_back(newTriangle.at(5));
            triangles.emplace_back(newTriangle.at(2));

            triangles.emplace_back(newTriangle.at(3));
            triangles.emplace_back(newTriangle.at(5));
            triangles.emplace_back(newTriangle.at(4));
        }
        vertex.clear();
        vertex = triangles;
        triangles.clear();
    }
    return vertex;
}
