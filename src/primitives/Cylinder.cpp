/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Cylinder.hpp"

static std::vector<Triangle> GenerateCylinderTriangles(const CylinderProperties &properties)
{
    std::vector<Triangle> triangles;
    std::vector<glm::vec3> verticesTop;
    std::vector<glm::vec3> verticesBottom;
    float r = properties.GetRadius();
    float h = properties.GetHeight();
    float precision = 50;
    float theta = 2 * M_PI / precision;
    glm::vec3 top = {0.0f, -h, 0.0f};
    glm::vec3 bottom = {0.0f, h, 0.0f};

    for (int i = 0; i < precision; i++) {
        verticesTop.push_back({r * (float)cos(i * theta), -h, r * (float)sin(i * theta)});
        verticesBottom.push_back({r * (float)cos(theta * ((double)i + 2 * M_PI / (precision * 2))), h, r * (float)sin(theta * ((double)i + 2 * M_PI / (precision * 2)))});
    }

    //top triangles
    for (std::size_t i = 0; i < verticesTop.size(); i++) {
        if (i == verticesTop.size() - 1)
            triangles.push_back({top, verticesTop[i], verticesTop[0], {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} , {0, 0}, {0, 0}});
        else
            triangles.push_back({top, verticesTop[i], verticesTop[i + 1], {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} , {0, 0}, {0, 0}});
    }
    //bottom triangles
    for (std::size_t i = 0; i < verticesBottom.size(); i++) {
        if (i == verticesBottom.size() - 1)
            triangles.push_back({bottom, verticesBottom[0], verticesBottom[i], {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} , {0, 0}, {0, 0}});
        else
            triangles.push_back({bottom, verticesBottom[i + 1], verticesBottom[i], {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} , {0, 0}, {0, 0}});
    }
    //top start triangles
    for (std::size_t i = 0; i < verticesTop.size(); i++) {
        if (i == verticesTop.size() - 1)
            triangles.push_back({verticesBottom[i], verticesTop[0], verticesTop[i], {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} , {0, 0}, {0, 0}});
        else
            triangles.push_back({verticesBottom[i], verticesTop[i + 1], verticesTop[i], {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} , {0, 0}, {0, 0}});
    }
    //bottom start triangles
    for (std::size_t i = 0; i < verticesBottom.size(); i++) {
        if (i == verticesBottom.size() - 1)
            triangles.push_back({verticesBottom[i], verticesBottom[0], verticesTop[0], {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} , {0, 0}, {0, 0}});
        else
            triangles.push_back({verticesBottom[i], verticesBottom[i + 1], verticesTop[i + 1], {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} , {0, 0}, {0, 0}});
    }

    for (std::size_t i = 0; i < precision; i++) {
        triangles.at(i).normalV0 = {0, -1, 0};
        triangles.at(i).normalV1 = {0, -1, 0};
        triangles.at(i).normalV2 = {0, -1, 0};

        triangles.at(i + precision).normalV0 = {0, 1, 0};
        triangles.at(i + precision).normalV1 = {0, 1, 0};
        triangles.at(i + precision).normalV2 = {0, 1, 0};
    }
    for (std::size_t i = 2 * precision; i < 2 * precision + precision; i++) {
        glm::vec3 point = {cos(i * theta), 0, sin(i * theta)};
        glm::vec3 tmpNormal1 = glm::normalize(triangles.at(i).v0);
        glm::vec3 tmpNormal2 = glm::normalize(triangles.at(i).v1);
        glm::vec3 tmpNormal3 = glm::normalize(triangles.at(i).v2);
        glm::vec3 tmpNormal4 = glm::normalize(triangles.at(i + precision).v0);
        glm::vec3 tmpNormal5 = glm::normalize(triangles.at(i + precision).v1);
        glm::vec3 tmpNormal6 = glm::normalize(triangles.at(i + precision).v2);

        tmpNormal1.y = 0;
        tmpNormal2.y = 0;
        tmpNormal3.y = 0;
        tmpNormal4.y = 0;
        tmpNormal5.y = 0;
        tmpNormal6.y = 0;
        tmpNormal1 = glm::normalize(tmpNormal1);
        tmpNormal2 = glm::normalize(tmpNormal2);
        tmpNormal3 = glm::normalize(tmpNormal3);
        tmpNormal4 = glm::normalize(tmpNormal4);
        tmpNormal5 = glm::normalize(tmpNormal5);
        tmpNormal6 = glm::normalize(tmpNormal6);
        triangles.at(i).normalV0 = tmpNormal1;
        triangles.at(i).normalV1 = tmpNormal2;
        triangles.at(i).normalV2 = tmpNormal3;
        triangles.at(i + precision).normalV0 = tmpNormal4;
        triangles.at(i + precision).normalV1 = tmpNormal5;
        triangles.at(i + precision).normalV2 = tmpNormal6;
    }
    return triangles;
}

Cylinder::Cylinder() : Object()
{
    _properties = CylinderProperties();
}

Cylinder::Cylinder(const Material &material, const Transform &transform, const std::vector<Texture> &textures, float radius, float height) : Object(material, transform, std::vector<Triangle>(), textures)
{
    _properties = CylinderProperties(radius, height);
    _triangles = GenerateCylinderTriangles(_properties);
}

Cylinder::Cylinder(const Material &material, const Transform &transform, const std::vector<Texture> &textures, const CylinderProperties &properties) : Object(material, transform, std::vector<Triangle>(), textures)
{
    _properties = properties;
    _triangles = GenerateCylinderTriangles(properties);
}

Cylinder::Cylinder(const Cylinder &other) : Object(other)
{
    _properties = other.getProperties();
    _triangles = GenerateCylinderTriangles(_properties);
}

Cylinder::Cylinder(JsonObject *obj) : Object(obj)
{
    _properties = CylinderProperties(obj);
    _triangles = GenerateCylinderTriangles(_properties);
}

Cylinder::Cylinder(CylinderProperties &cylinder) : Object(cylinder)
{
    _properties = cylinder;
    _triangles = GenerateCylinderTriangles(cylinder);
}

CylinderProperties Cylinder::getProperties() const
{
    return _properties;
}

CylinderProperties &Cylinder::getProperties()
{
    return _properties;
}

void Cylinder::setProperties(CylinderProperties &properties)
{
    _properties = properties;
    _triangles = GenerateCylinderTriangles(properties);
}
