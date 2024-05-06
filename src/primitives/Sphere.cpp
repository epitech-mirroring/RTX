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

std::vector<Triangle> Sphere::generateVertices(const SphereProperties &properties) {
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

    std::vector<Triangle> triangles;

    Triangle triangle;
    triangle.v0 = vertices.at(0);
    triangle.v1 = vertices.at(1);
    triangle.v2 = vertices.at(2);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(0);
    triangle.v1 = vertices.at(2);
    triangle.v2 = vertices.at(3);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(0);
    triangle.v1 = vertices.at(3);
    triangle.v2 = vertices.at(4);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(0);
    triangle.v1 = vertices.at(4);
    triangle.v2 = vertices.at(5);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(0);
    triangle.v1 = vertices.at(5);
    triangle.v2 = vertices.at(1);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(1);
    triangle.v1 = vertices.at(6);
    triangle.v2 = vertices.at(2);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(2);
    triangle.v1 = vertices.at(7);
    triangle.v2 = vertices.at(3);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(3);
    triangle.v1 = vertices.at(8);
    triangle.v2 = vertices.at(4);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(4);
    triangle.v1 = vertices.at(9);
    triangle.v2 = vertices.at(5);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(5);
    triangle.v1 = vertices.at(10);
    triangle.v2 = vertices.at(1);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(6);
    triangle.v1 = vertices.at(7);
    triangle.v2 = vertices.at(2);

    triangle.v0 = vertices.at(7);
    triangle.v1 = vertices.at(3);
    triangle.v2 = vertices.at(8);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(8);
    triangle.v1 = vertices.at(4);
    triangle.v2 = vertices.at(9);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(9);
    triangle.v1 = vertices.at(5);
    triangle.v2 = vertices.at(10);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(10);
    triangle.v1 = vertices.at(1);
    triangle.v2 = vertices.at(6);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(11);
    triangle.v1 = vertices.at(6);
    triangle.v2 = vertices.at(7);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(11);
    triangle.v1 = vertices.at(7);
    triangle.v2 = vertices.at(8);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(11);
    triangle.v1 = vertices.at(8);
    triangle.v2 = vertices.at(9);
    triangles.emplace_back(triangle);

    triangle.v0 = vertices.at(11);
    triangle.v1 = vertices.at(10);
    triangle.v2 = vertices.at(6);
    triangles.emplace_back(triangle);

    return Sphere::duplicateTriangles(triangles);
}

std::vector<Triangle> Sphere::duplicateTriangles(std::vector<Triangle>& triangles)
{
    std::vector<glm::vec3> newTriangle;
    std::vector<Triangle> vertex = triangles;
    Triangle triangle;

    for (std::size_t j = 0; j < 3; j++) {
        for (std::size_t i = 0; i < triangles.size(); i++) {
            newTriangle.clear();
            vertex.clear();
            newTriangle.emplace_back(vertex.at(i).v0);
            newTriangle.emplace_back(vertex.at(i).v1);
            newTriangle.emplace_back(vertex.at(i).v2);
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

            triangle.v0 = newTriangle.at(0);
            triangle.v1 = newTriangle.at(3);
            triangle.v2 = newTriangle.at(4);
            vertex.emplace_back(triangle);

            triangle.v0 = newTriangle.at(3);
            triangle.v1 = newTriangle.at(1);
            triangle.v2 = newTriangle.at(5);
            vertex.emplace_back(triangle);

            triangle.v0 = newTriangle.at(4);
            triangle.v1 = newTriangle.at(5);
            triangle.v2 = newTriangle.at(2);
            vertex.emplace_back(triangle);

            triangle.v0 = newTriangle.at(3);
            triangle.v1 = newTriangle.at(5);
            triangle.v2 = newTriangle.at(4);
            vertex.emplace_back(triangle);
        }
        triangles.clear();
        triangles = vertex;
    }
    for (std::size_t i = 0; i < triangles.size(); i++) {
        auto triangleNorme = (float)pow(triangles.at(i).v0.x * triangles.at(i).v0.x +
                    triangles.at(i).v0.y * triangles.at(i).v0.y +
                    triangles.at(i).v0.z * triangles.at(i).v0.z,
            0.5);
        glm::vec3 AB;
        AB.x = triangles.at(i).v1.x - triangles.at(i).v0.x;
        AB.y = triangles.at(i).v1.y - triangles.at(i).v0.y;
        AB.z = triangles.at(i).v1.z - triangles.at(i).v0.z;
        glm::vec3 AC;
        AC.x = triangles.at(i).v2.x - triangles.at(i).v0.x;
        AC.y = triangles.at(i).v2.y - triangles.at(i).v0.y;
        AC.z = triangles.at(i).v2.z - triangles.at(i).v0.z;
        glm::vec3 BC;
        BC.x = triangles.at(i).v2.x - triangles.at(i).v1.x;
        BC.y = triangles.at(i).v2.y - triangles.at(i).v1.y;
        BC.z = triangles.at(i).v2.z - triangles.at(i).v1.z;
        triangles.at(i).normalV0 = (AB * AC) / triangleNorme;
        triangles.at(i).normalV1 = (AB * BC) / triangleNorme;
        triangles.at(i).normalV2 = (BC * AC) / triangleNorme;
    }
    return triangles;
}
