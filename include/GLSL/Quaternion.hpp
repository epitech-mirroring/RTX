/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <stdexcept>
#include "json/Json.hpp"

namespace GLSL {
    class Quaternion {
    public:
        double x = 0;
        double y = 0;
        double z = 0;
        double w = 0;

        Quaternion() = default;
        Quaternion(double x, double y, double z, double w=1);
        Quaternion(const Quaternion &q) = default;
        Quaternion(JsonObject *obj);
        ~Quaternion() = default;

        Quaternion &operator=(const Quaternion &q) = default;
        Quaternion operator*(const Quaternion &q) const;
        Quaternion operator*(double f) const;
        Quaternion operator+(const Quaternion &q) const;
        Quaternion operator-(const Quaternion &q) const;
        Quaternion operator/(double f) const;
        Quaternion operator-() const;
        Quaternion &operator*=(const Quaternion &q);
        Quaternion &operator*=(double f);
        Quaternion &operator+=(const Quaternion &q);
        Quaternion &operator-=(const Quaternion &q);
        Quaternion &operator/=(double f);
        bool operator==(const Quaternion &q) const;
        bool operator!=(const Quaternion &q) const;
        double &operator[](int i);
        [[nodiscard]] double length() const;
    };
}
