/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Cube.hpp"
#include <utility>

static std::vector<Triangle> createCubeTriangles(float size)
{
    // Triangle struct is
    // vec3 a
    // vec3 b
    // vec3 c
    // vec3 normal_a
    // vec3 normal_b
    // vec3 normal_c
    // Coordinates are in 3D space
    // x is left to right
    // y is top to bottom (the higher the value, the lower the point)
    // z is front to back
    // The center of the cube is at (0, 0, 0)
    double offset = size / 2.f;
    std::vector<Triangle> triangles = {
        // Front
            {{-offset, -offset, -offset}, {-offset, offset, -offset}, {offset, offset, -offset}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}},
            {{-offset, -offset, -offset}, {offset, offset, -offset}, {offset, -offset, -offset}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}},
        // Back
            {{-offset, -offset, offset}, {offset, -offset, offset}, {offset, offset, offset}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}},
            {{-offset, -offset, offset}, {offset, offset, offset}, {-offset, offset, offset}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}},
        // Left
            {{-offset, -offset, -offset}, {-offset, -offset, offset}, {-offset, offset, offset}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}},
            {{-offset, -offset, -offset}, {-offset, offset, offset}, {-offset, offset, -offset}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}},
        // Right
            {{offset, -offset, -offset}, {offset, offset, -offset}, {offset, offset, offset}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}},
            {{offset, -offset, -offset}, {offset, offset, offset}, {offset, -offset, offset}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}},
        // Top
            {{-offset, offset, -offset}, {-offset, offset, offset}, {offset, offset, offset}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}},
            {{-offset, offset, -offset}, {offset, offset, offset}, {offset, offset, -offset}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}},
        // Bottom
            {{-offset, -offset, -offset}, {offset, -offset, -offset}, {offset, -offset, offset}, {0, -1, 0}, {0, -1, 0}, {0, -1, 0}},
            {{-offset, -offset, -offset}, {offset, -offset, offset}, {-offset, -offset, offset}, {0, -1, 0}, {0, -1, 0}, {0, -1, 0}},
    };
    return triangles;
}

Cube::Cube()
{
    _properties = CubeProperties();
}

Cube::Cube(const Material& material, const Transform& transform, const std::vector<Texture>& textures, float size) : Object(material, transform, createCubeTriangles(size), textures)
{
    _properties.setSize(size);
}

Cube::Cube(const Material& material, const Transform& transform, const std::vector<Texture>& textures, const CubeProperties& properties) : Object(material, transform, createCubeTriangles(properties.getSize()), textures)
{
    _properties = properties;
}

Cube::Cube(const Cube &other)
 : Object(other) {
    _properties = other._properties;
    this->_triangles = other._triangles;
}

Cube::Cube(JsonObject *obj)
{
    _properties = CubeProperties(obj);
    _triangles = createCubeTriangles(_properties.getSize());
}

Cube::Cube(CubeProperties &properties): Object(properties)
{
    _properties = properties;
    _triangles = createCubeTriangles(properties.getSize());
}

CubeProperties Cube::getProperties() const {
    return _properties;
}

CubeProperties &Cube::getProperties()
{
    return _properties;
}

float &Cube::getSize()
{
    return _properties.getSize();
}

float Cube::getSize() const
{
    return _properties.getSize();
}
