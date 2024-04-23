/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <cstddef>
#include <cmath>
#include <cstdarg>
#include <stdexcept>

namespace GLSL {
    template <int N>
    class Vector {
    protected:
        float _data[N];
    public:
        Vector() {
            for (int i = 0; i < N; i++) {
                _data[i] = 0;
            }
        };
        Vector(float values...) {
            va_list args;
            va_start(args, values);
            for (int i = 0; i < N; i++) {
                _data[i] = va_arg(args, float);
            }
            va_end(args);
        };
        Vector(const Vector<N> &other) {
            for (int i = 0; i < N; i++) {
                _data[i] = other[i];
            }
        };
        ~Vector() = default;

        double length() const {
            double sum = 0;
            for (int i = 0; i < N; i++) {
                sum += _data[i] * _data[i];
            }
            return sqrt(sum);
        };
        double dot(const Vector<N> &other) const {
            double sum = 0;
            for (int i = 0; i < N; i++) {
                sum += _data[i] * other[i];
            }
            return sum;
        };

        float &operator[](std::size_t index) {
            return _data[index];
        };
        const float &operator[](std::size_t index) const {
            return _data[index];
        };

        bool operator==(const Vector<N> &other) const {
            for (int i = 0; i < N; i++) {
                if (_data[i] != other[i]) {
                    return false;
                }
            }
            return true;
        };
        bool operator!=(const Vector<N> &other) const {
            return !(*this == other);
        };

        Vector<N> operator+(const Vector<N> &other) const {
            Vector<N> result;
            for (int i = 0; i < N; i++) {
                result[i] = _data[i] + other[i];
            }
            return result;
        };
        Vector<N> operator-(const Vector<N> &other) const {
            Vector<N> result;
            for (int i = 0; i < N; i++) {
                result[i] = _data[i] - other[i];
            }
            return result;
        };
        Vector<N> operator*(const Vector<N> &other) const {
            if (this->_data.size() != other._data.size()) {
                throw std::invalid_argument("Vectors must have the same dimensions to be multiplied");
            }
            Vector<N> result;
            for (int i = 0; i < N; ++i) {
                int next_i = (i + 1) % N;
                int prev_i = (i - 1 + N) % N;
                result[i] = this[next_i] * other[prev_i] - this[prev_i] * other[next_i];
            }
            return result;
        };
        Vector<N> operator/(const Vector<N> &other) const {
            Vector<N> result;
            if (this->_data.size() != other._data.size()) {
                throw std::invalid_argument("Vectors must have the same dimensions to be divided");
            }
            result.reserve(N);
            for (size_t i = 0; i < N; ++i) {
                if (other[i] == 0) {
                    throw std::invalid_argument("Division par zéro.");
                }
                result[i] = this[i] / other[i];
            }
            return result;
        };
        Vector<N> operator*(float scalar) const {
            Vector<N> result;
            for (int i = 0; i < N; i++) {
                result[i] = _data[i] * scalar;
            }
            return result;
        };
        Vector<N> operator/(float scalar) const {
            Vector<N> result;
            for (int i = 0; i < N; i++) {
                result[i] = _data[i] / scalar;
            }
            return result;
        };

        // Swizzling
        float x() const {
            return _data[0];
        };
        float y() const {
            return _data[1];
        };
        float z() const {
            return _data[2];
        };
        float w() const {
            return _data[3];
        };

        float r() const {
            return _data[0];
        };
        float g() const {
            return _data[1];
        };
        float b() const {
            return _data[2];
        };
        float a() const {
            return _data[3];
        };
    };
}
