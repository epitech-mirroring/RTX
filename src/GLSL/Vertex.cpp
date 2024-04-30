/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "GLSL/Vertex.hpp"
using namespace GLSL;

Vertex::Vertex() {
    _position = Vector<3>(0.0, 0.0, 0.0);
    _normal = Vector<3>(0.0, 0.0, 0.0);
    _uv = Vector<2>(0.0, 0.0);
};

Vertex::Vertex(const Vector<3>& position, const Vector<3>& normal, const Vector<2>& uv) {
    _position = position;
    _normal = normal;
    _uv = uv;
};

Vertex::Vertex(const Vertex &other) {
    _position = other.getPosition();
    _normal = other.getNormal();
    _uv = other.getUV();
};

Vector<3> Vertex::getPosition() const {
    return _position;
};

Vector<3> Vertex::getNormal() const {
    return _normal;
};

Vector<2> Vertex::getUV() const {
    return _uv;
};

void Vertex::setPosition(const Vector<3>& position) {
    _position = position;
};

void Vertex::setNormal(const Vector<3>& normal) {
    _normal = normal;
};

void Vertex::setUV(const Vector<2>& uv) {
    _uv = uv;
};
