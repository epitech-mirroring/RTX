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

Sphere::Sphere(const Material& material, const Transform& transform, const std::vector<Texture>& textures, float radius) : Object(material, transform, std::vector<Triangle>(), textures)
{
    _properties.setRadius(radius);
}

Sphere::Sphere(const Material& material, const Transform& transform, const std::vector<Texture>& textures, const SphereProperties& properties) : Object(material, transform, Sphere::generateVertices(properties), textures)
{
    _properties = properties;
}

Sphere::Sphere(const Sphere &other) : Object(other) {
    _properties = other._properties;
}

Sphere::Sphere(JsonObject *obj)
{
    _properties = SphereProperties(obj);
    _triangles = Sphere::generateVertices(_properties);
}

Sphere::Sphere(SphereProperties &properties) : Object(properties)
{
    _properties = properties;
    _triangles = Sphere::generateVertices(properties);
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
    float r = properties.getRadius();
    float j = -r + (float)sqrt(2 * pow(r, 2) * 3);
    float topY = r - j;
    float bottomY = -topY;
    float theta = 2 * M_PI / 5;
    glm::vec3 top = {0.0f, -r, 0.0f};
    glm::vec3 bottom = {0.0f, r, 0.0f};
    std::vector<glm::vec3> vertices;

    vertices.push_back(top);
    for (std::size_t i = 0; i < 5; i++) {
        auto x = (float)cos(theta * (double)i);
        auto z = (float)sin(theta * (double)i);
        vertices.emplace_back(x, topY, z);
    }
    vertices.push_back(bottom);
    for (std::size_t i = 0; i < 5; i++) {
        auto x = (float)cos(theta * ((double)i + 2 * M_PI / 10));
        auto z = (float)sin(theta * ((double)i + 2 * M_PI / 10));
        vertices.emplace_back(x, bottomY, z);
    }

    std::vector<Triangle> triangles;
    Triangle triangle{};

    std::vector<std::array<int, 3>> array = {
            {0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4, 5}, {0, 5, 1},
            {6, 8, 7}, {6, 9, 8}, {6, 10, 9}, {6, 11, 10}, {6, 7, 11},
            {2, 1, 7}, {3, 2, 8}, {4, 3, 9}, {5, 4, 10}, {1, 5, 11},
            {7, 8, 2}, {8, 9, 3}, {9, 10, 4}, {10, 11, 5}, {11, 7, 1}
    };

    for (const auto& tmp : array) {
        triangle.v0 = vertices.at(tmp[0]);
        triangle.v1 = vertices.at(tmp[1]);
        triangle.v2 = vertices.at(tmp[2]);
        triangles.emplace_back(triangle);
    }
    triangles = Sphere::duplicateTriangles(triangles, r);
    return triangles;
}

glm::vec3 getMiddle(const glm::vec3 &a, const glm::vec3 &b)
{
    glm::vec3 c;

    c.x = (a.x + b.x) / 2.f;
    c.y = (a.y + b.y) / 2.f;
    c.z = (a.z + b.z) / 2.f;
    return c;
}

std::vector<Triangle> Sphere::duplicateTriangles(std::vector<Triangle>& triangles, float radius)
{
    std::vector<glm::vec3> newTriangle;
    std::vector<Triangle> vertex;

    for (std::size_t j = 0; j < 4; j++) {
        vertex.clear();
        for (auto &triangle : triangles) {
            glm::vec3 h1 = getMiddle(triangle.v0, triangle.v1);
            glm::vec3 h2 = getMiddle(triangle.v1, triangle.v2);
            glm::vec3 h3 = getMiddle(triangle.v2, triangle.v0);
            vertex.push_back({triangle.v0, h1, h3, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
            vertex.push_back({h1, triangle.v1, h2, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
            vertex.push_back({h3, h2, triangle.v2, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
            vertex.push_back({h3, h1, h2, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
        }
        triangles.clear();
        triangles = vertex;
    }
    for (auto &triangle: triangles) {
        triangle.v0 = glm::normalize(triangle.v0) * radius;
        triangle.v1 = glm::normalize(triangle.v1) * radius;
        triangle.v2 = glm::normalize(triangle.v2) * radius;
    }
    for (auto &t : triangles) {
        t.normalV0 = glm::normalize(t.v0);
        t.normalV1 = glm::normalize(t.v1);
        t.normalV2 = glm::normalize(t.v2);
    }
    return triangles;
}
