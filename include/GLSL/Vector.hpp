/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <cstddef>

namespace GLSL {
    template <int N>
    class Vector {
    private:
        float _data[N];
    public:
        Vector();
        Vector(float values...);
        Vector(const Vector<N> &other);
        ~Vector();

        double length() const;
        double dot(const Vector<N> &other) const;

        float &operator[](std::size_t index);
        const float &operator[](std::size_t index) const;

        bool operator==(const Vector<N> &other) const;
        bool operator!=(const Vector<N> &other) const;

        Vector<N> operator+(const Vector<N> &other) const;
        Vector<N> operator-(const Vector<N> &other) const;
        Vector<N> operator*(const Vector<N> &other) const;
        Vector<N> operator/(const Vector<N> &other) const;
        Vector<N> operator*(float scalar) const;
        Vector<N> operator/(float scalar) const;

        // Swizzling
        float x() const;
        float y() const;
        float z() const;
        float w() const;

        float r() const;
        float g() const;
        float b() const;
        float a() const;
    };
}
