/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <GLSL/Color.hpp>
#include <GLSL/Quaternion.hpp>
using namespace GLSL;

Quaternion::Quaternion(const double x, const double y, const double z, const double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Quaternion::Quaternion(JsonObject *obj) {
    x = obj->getFloat("x");
    y = obj->getFloat("y");
    z = obj->getFloat("z");
    w = obj->getFloat("w");
}

Quaternion Quaternion::operator*(const Quaternion &q) const {
    double _x = this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y;
    double _y = this->w * q.y + this->y * q.w + this->z * q.x - this->x * q.z;
    double _z = this->w * q.z + this->z * q.w + this->x * q.y - this->y * q.x;
    double _w = this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z;
    return {_x, _y, _z, _w};
}

Quaternion Quaternion::operator*(const double f) const {
    return {x * f, y * f, z * f, w * f};
}

Quaternion Quaternion::operator+(const Quaternion &q) const {
    return {x + q.x, y + q.y, z + q.z, w + q.w};
}

Quaternion Quaternion::operator-(const Quaternion &q) const {
    return {x - q.x, y - q.y, z - q.z, w - q.w};
}

Quaternion Quaternion::operator/(const double f) const {
    return {x / f, y / f, z / f, w / f};
}

Quaternion Quaternion::operator-() const {
    return {-x, -y, -z, -w};
}

Quaternion &Quaternion::operator*=(const Quaternion &q) {
    *this = *this * q;
    return *this;
}

Quaternion &Quaternion::operator*=(const double f) {
    *this = *this * f;
    return *this;
}

Quaternion &Quaternion::operator+=(const Quaternion &q) {
    *this = *this + q;
    return *this;
}

Quaternion &Quaternion::operator-=(const Quaternion &q) {
    *this = *this - q;
    return *this;
}

Quaternion &Quaternion::operator/=(const double f) {
    *this = *this / f;
    return *this;
}

bool Quaternion::operator==(const Quaternion &q) const {
    return x == q.x && y == q.y && z == q.z && w == q.w;
}

bool Quaternion::operator!=(const Quaternion &q) const {
    return x != q.x || y != q.y || z != q.z || w != q.w;
}

double &Quaternion::operator[](const int i) {
    switch (i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::out_of_range("Quaternion index out of range");
    }
}

double Quaternion::length() const {
    return sqrt(x * x + y * y + z * z + w * w);
}
