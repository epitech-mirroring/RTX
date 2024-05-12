/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Plane.hpp"

static std::vector<Triangle> createPlaneTriangles(PlaneProperties &properties) {
    std::vector<Triangle> triangles;
    Triangle triangle1{};
    Triangle triangle2{};
    float width = properties.getWidth();
    float height = properties.getHeight();

    triangle1.v0 =  glm::vec3 {-width / 2, 0, -height / 2};
    triangle1.v1 =  glm::vec3 {width / 2, 0, -height / 2};
    triangle1.v2 =  glm::vec3 {width / 2, 0, height / 2};
    triangle1.normalV0 = glm::vec3 {0, -1, 0};
    triangle1.normalV1 = glm::vec3 {0, -1, 0};
    triangle1.normalV2 = glm::vec3 {0, -1, 0};
    triangle1.uv0 = glm::vec2 {0, 0};
    triangle1.uv1 = glm::vec2 {1, 0};
    triangle1.uv2 = glm::vec2 {1, 1};


    triangle2.v0 =  glm::vec3 {-width / 2, 0, -height / 2};
    triangle2.v1 =  glm::vec3 {width / 2, 0, height / 2};
    triangle2.v2 =  glm::vec3 {-width / 2, 0, height / 2};
    triangle2.normalV0 = glm::vec3 {0, -1, 0};
    triangle2.normalV1 = glm::vec3 {0, -1, 0};
    triangle2.normalV2 = glm::vec3 {0, -1, 0};
    triangle2.uv0 = glm::vec2 {0, 0};
    triangle2.uv1 = glm::vec2 {1, 1};
    triangle2.uv2 = glm::vec2 {0, 1};

    triangles.push_back(triangle1);
    triangles.push_back(triangle2);
    return triangles;
}

Plane::Plane() : Object() {
    _properties = PlaneProperties();
}

Plane::Plane(PlaneProperties &properties) : Object(properties) {
    _properties = properties;
    _triangles = createPlaneTriangles(_properties);
}

Plane::Plane(const Material &material, const Transform &transform, const std::vector<Texture> &textures, float height, float width) : Object(material, transform, std::vector<Triangle>(), textures) {
    _properties = PlaneProperties(height, width);
    _triangles = createPlaneTriangles(_properties);
}

PlaneProperties Plane::getProperties() const {
    return _properties;
}

PlaneProperties &Plane::getProperties() {
    return _properties;
}

void Plane::setProperties(PlaneProperties &properties) {
    _properties = properties;
}
