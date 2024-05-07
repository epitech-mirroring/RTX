/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Plane.hpp"

static std::vector<Triangle> createPlaneTriangles(PlaneProperties *properties) {
    std::vector<Triangle> triangles;
    Triangle triangle1;
    Triangle triangle2;
    float width = properties->getWidth();
    float height = properties->getHeight();

    triangle1.v0 =  glm::vec3 {};
    return triangles;
}

Plane::Plane() {
    _properties = new PlaneProperties();
}

Plane::Plane(PlaneProperties *properties) {
    _properties = properties;
}

Plane::Plane(const Material &material, const Transform &transform, const std::vector<Texture> &textures, float height, float width) : Object(material, transform, createPlaneTriangles(_properties), textures) {
    _properties = new PlaneProperties(height, width);
}

PlaneProperties *Plane::getProperties() const {
    return _properties;
}

PlaneProperties *Plane::getProperties() {
    return _properties;
}

void Plane::setProperties(PlaneProperties *properties) {
    _properties = properties;
}
