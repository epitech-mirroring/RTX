/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Torus.hpp"

static std::vector<Triangle> GenerateTorusTriangles(const TorusProperties &properties)
{
    std::vector<Triangle> triangles;
    float r = properties.GetRadius();
    float mR = properties.GetMiddleRadius();
    float precisionCircle = 25;
    float thetaCircle = 2 * M_PI / precisionCircle;
    float precisionTorus = 90;
    float thetaTorus = 2 * M_PI / precisionTorus;
    std::vector<std::vector<glm::vec3>> torusCircles;
    std::vector<glm::vec3> circle;

    for (std::size_t i = 0; i < precisionTorus; i++) {
        circle.clear();
        for (std::size_t j = 0; j < precisionCircle; j++) {
            float x = (mR + r * cos(j * thetaCircle)) * cos(i * thetaTorus);
            float z = (mR + r * cos(j * thetaCircle)) * sin(i * thetaTorus);
            float y = r * sin(j * thetaCircle);
            circle.push_back(glm::vec3(x, y, z));
        }
        torusCircles.push_back(circle);
    }
    for (std::size_t i = 0; i < precisionTorus; i++) {
        for (std::size_t j = 0; j < precisionCircle; j++) {
            glm::vec3 a = torusCircles[i][j];
            glm::vec3 b =
                    torusCircles[(i + 1) % (std::size_t) precisionTorus][j];
            glm::vec3 c =
                    torusCircles[(i + 1) % (std::size_t) precisionTorus]
                                [(j + 1) % (std::size_t) precisionCircle];
            glm::vec3 d = torusCircles[i][(j + 1) %
                                          (std::size_t) precisionCircle];
            glm::vec3 circleCenter = torusCircles[i][j];
            float xCenter = cos(i * thetaTorus);
            float zCenter = sin(i * thetaTorus);
            float yCenter = 0;
            glm::vec3 center = glm::vec3(xCenter, yCenter, zCenter);
            float xCenterNext = cos(((i + 1) % (std::size_t) precisionTorus) * thetaTorus);
            float zCenterNext = sin(((i + 1) % (std::size_t) precisionTorus) * thetaTorus);
            float yCenterNext = 0;
            glm::vec3 centerNext = glm::vec3(xCenterNext, yCenterNext, zCenterNext);
            triangles.push_back({a, b, c});
            triangles.back().normalV0 = glm::normalize(a - center);
            triangles.back().normalV1 = glm::normalize(b - centerNext);
            triangles.back().normalV2 = glm::normalize(c - centerNext);
            triangles.push_back({a, c, d});
            triangles.back().normalV0 = glm::normalize(a - center);
            triangles.back().normalV1 = glm::normalize(c - centerNext);
            triangles.back().normalV2 = glm::normalize(d - center);
        }
    }
    return triangles;
}

Torus::Torus() : Object()
{
    _properties = TorusProperties();
}

Torus::Torus(const Material &material, const Transform &transform, const std::vector<Texture> &textures, float radius, float height) : Object(material, transform, std::vector<Triangle>(), textures)
{
    _properties = TorusProperties(radius, height);
    _triangles = GenerateTorusTriangles(_properties);
}

Torus::Torus(const Material &material, const Transform &transform, const std::vector<Texture> &textures, const TorusProperties &properties) : Object(material, transform, std::vector<Triangle>(), textures)
{
    _properties = properties;
    _triangles = GenerateTorusTriangles(properties);
}

Torus::Torus(const Torus &other) : Object(other)
{
    _properties = other.getProperties();
    _triangles = GenerateTorusTriangles(_properties);
}

Torus::Torus(JsonObject *obj) : Object(obj)
{
    _properties = TorusProperties(obj);
    _triangles = GenerateTorusTriangles(_properties);
}

Torus::Torus(TorusProperties &cylinder) : Object(cylinder)
{
    _properties = cylinder;
    _triangles = GenerateTorusTriangles(cylinder);
}

TorusProperties Torus::getProperties() const
{
    return _properties;
}

TorusProperties &Torus::getProperties()
{
    return _properties;
}

void Torus::setProperties(TorusProperties &properties)
{
    _properties = properties;
    _triangles = GenerateTorusTriangles(properties);
}
