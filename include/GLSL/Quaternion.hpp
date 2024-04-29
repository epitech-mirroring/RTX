/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <stdexcept>

namespace GLSL {
    class Quaternion {
    public:
        double x = 0;
        double y = 0;
        double z = 0;
        double w = 0;

        Quaternion() = default;
        Quaternion(const double x, const double y, const double z, const double w=1) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }
        Quaternion(const Quaternion &q) = default;
        ~Quaternion() = default;

        Quaternion &operator=(const Quaternion &q) = default;
        Quaternion operator*(const Quaternion &q) const {
            double x = this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y;
            double y = this->w * q.y + this->y * q.w + this->z * q.x - this->x * q.z;
            double z = this->w * q.z + this->z * q.w + this->x * q.y - this->y * q.x;
            double w = this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z;
            return {x, y, z, w};
        }
        Quaternion operator*(const double f) const {
            return {x * f, y * f, z * f, w * f};
        }
        Quaternion operator+(const Quaternion &q) const {
            return {x + q.x, y + q.y, z + q.z, w + q.w};
        }
        Quaternion operator-(const Quaternion &q) const {
            return {x - q.x, y - q.y, z - q.z, w - q.w};
        }
        Quaternion operator/(const double f) const {
            return {x / f, y / f, z / f, w / f};
        }
        Quaternion operator-() const {
            return {-x, -y, -z, -w};
        }
        Quaternion &operator*=(const Quaternion &q) {
            *this = *this * q;
            return *this;
        }
        Quaternion &operator*=(const double f) {
            *this = *this * f;
            return *this;
        }
        Quaternion &operator+=(const Quaternion &q) {
            *this = *this + q;
            return *this;
        }
        Quaternion &operator-=(const Quaternion &q) {
            *this = *this - q;
            return *this;
        }
        Quaternion &operator/=(const double f) {
            *this = *this / f;
            return *this;
        }
        bool operator==(const Quaternion &q) const {
            return x == q.x && y == q.y && z == q.z && w == q.w;
        }
        bool operator!=(const Quaternion &q) const {
            return x != q.x || y != q.y || z != q.z || w != q.w;
        }
        double &operator[](const int i) {
            switch (i) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
                default: throw std::out_of_range("Quaternion index out of range");
            }
        }
        [[nodiscard]] double length() const {
            return sqrt(x * x + y * y + z * z + w * w);
        }
    };
}
