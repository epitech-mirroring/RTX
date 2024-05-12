/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Cone.hpp"

static std::vector<Triangle> GenerateConeTriangles(const ConeProperties &properties)
{
    std::vector<Triangle> triangles;
    std::vector<glm::vec3> verticesTop;
    std::vector<glm::vec3> verticesBottom;
    float r = properties.GetRadius();
    float h = properties.GetHeight();
    float precision = 50;
    float oppening = atan(r / h);
    float theta = 2 * M_PI / precision;
    glm::vec3 top = {0.0f, -h, 0.0f};
    glm::vec3 bottom = {0.0f, h, 0.0f};

    for (int i = 0; i < precision; i++) {
        verticesBottom.push_back({r * (float)cos(theta * ((double)i + 2 * M_PI / (precision * 2))), h, r * (float)sin(theta * ((double)i + 2 * M_PI / (precision * 2)))});
    }
    //bottom triangles
    for (std::size_t i = 0; i < verticesBottom.size(); i++) {
        if (i == verticesBottom.size() - 1)
            triangles.push_back({bottom, verticesBottom[0], verticesBottom[i], {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} , {0, 0}, {0, 0}});
        else
            triangles.push_back({bottom, verticesBottom[i + 1], verticesBottom[i], {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} , {0, 0}, {0, 0}});
    }
    //bottom start triangles
    for (std::size_t i = 0; i < verticesBottom.size(); i++) {
        if (i == verticesBottom.size() - 1)
            triangles.push_back({verticesBottom[i], verticesBottom[0], top, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} , {0, 0}, {0, 0}});
        else
            triangles.push_back({verticesBottom[i], verticesBottom[i + 1], top, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} , {0, 0}, {0, 0}});
    }

    for (std::size_t i = 0; i < precision; i++) {
        triangles.at(i).normalV0 = {0, -1, 0};
        triangles.at(i).normalV1 = {0, -1, 0};
        triangles.at(i).normalV2 = {0, -1, 0};
    }
    float oppositeDist = r * sin(atan(h / r));
    float bdDist = sqrt(pow(r, 2) - pow(oppositeDist, 2));

    for (std::size_t i = precision; i < 2 * precision; i++) {
        glm::vec3 bdVec = glm::normalize(top - triangles.at(i).v0) * bdDist;
        glm::vec3 adVec = triangles.at(i).v0 + bdVec;
        triangles.at(i).normalV0 = glm::normalize(adVec);
        bdVec = glm::normalize(top - triangles.at(i).v1) * bdDist;
        adVec = triangles.at(i).v1 + bdVec;
        triangles.at(i).normalV1 = glm::normalize(adVec);
        triangles.at(i).normalV2 = glm::vec3(0, 0, 0);
    }
    return triangles;
}

Cone::Cone() : Object()
{
    _properties = ConeProperties();
}

Cone::Cone(const Material &material, const Transform &transform, const std::vector<Texture> &textures, float radius, float height) : Object(material, transform, std::vector<Triangle>(), textures)
{
    _properties = ConeProperties(radius, height);
    _triangles = GenerateConeTriangles(_properties);
}

Cone::Cone(const Material &material, const Transform &transform, const std::vector<Texture> &textures, const ConeProperties &properties) : Object(material, transform, std::vector<Triangle>(), textures)
{
    _properties = properties;
    _triangles = GenerateConeTriangles(properties);
}

Cone::Cone(const Cone &other) : Object(other)
{
    _properties = other.getProperties();
    _triangles = GenerateConeTriangles(_properties);
}

Cone::Cone(JsonObject *obj) : Object(obj)
{
    _properties = ConeProperties(obj);
    _triangles = GenerateConeTriangles(_properties);
}

Cone::Cone(ConeProperties &cylinder) : Object(cylinder)
{
    _properties = cylinder;
    _triangles = GenerateConeTriangles(cylinder);
}

ConeProperties Cone::getProperties() const
{
    return _properties;
}

ConeProperties &Cone::getProperties()
{
    return _properties;
}

void Cone::setProperties(ConeProperties &properties)
{
    _properties = properties;
    _triangles = GenerateConeTriangles(properties);
}
