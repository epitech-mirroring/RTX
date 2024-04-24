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
    private:
        double _data[N];
    public:
        Vector() {
            for (int i = 0; i < N; i++) {
                _data[i] = 0;
            }
        };
        Vector(double value, ...) {
            va_list args;
            _data[0] = value;
            va_start(args, value);
            for (int i = 1; i < N; i++) {
                _data[i] = va_arg(args, double);
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

        double &operator[](std::size_t index) {
            return _data[index];
        };
        const double &operator[](std::size_t index) const {
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
            Vector<N> result;
            for (int i = 0; i < N; ++i) {
                int next_i = (i + 1) % N;
                int prev_i = (i - 1 + N) % N;
                result[i] = _data[next_i] * other[prev_i] - _data[prev_i] * other[next_i];
            }
            return result;
        };
        Vector<N> operator/(const Vector<N> &other) const {
            Vector<N> result;
            for (size_t i = 0; i < N; ++i) {
                if (other[i] == 0) {
                    throw std::invalid_argument("Division par zéro.");
                }
                result[i] = _data[i] / other[i];
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

        Vector<N> &operator+=(const Vector<N> &other) {
            *this = *this + other;
            return *this;
        };

        Vector<N> &operator-=(const Vector<N> &other) {
            *this = *this - other;
            return *this;
        };

        Vector<N> &operator*=(const Vector<N> &other) {
            *this = *this * other;
            return *this;
        };

        Vector<N> &operator/=(const Vector<N> &other) {
            *this = *this / other;
            return *this;
        };

        Vector<N> &operator*=(float scalar) {
            *this = *this * scalar;
            return *this;
        };

        Vector<N> &operator/=(float scalar) {
            *this = *this / scalar;
            return *this;
        };
        // Swizzling
        float x() const {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimension");
            }
            return _data[0];
        };
        Vector<1> x() {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimension");
            }
            return Vector<1>(_data[0]);
        };
        Vector<2> xx() {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<2>(_data[0], _data[0]);
        };
        Vector<2> xy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<2>(_data[0], _data[1]);
        };
        Vector<2> xz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[0], _data[2]);
        };
        Vector<2> xw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[0], _data[3]);
        };
        Vector<3> xxx() {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[0]);
        };
        Vector<3> xxy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[1]);
        };
        Vector<3> xxz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[2]);
        };
        Vector<3> xxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[3]);
        };
        Vector<3> xyx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[0]);
        };
        Vector<3> xyy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[1]);
        };
        Vector<3> xyz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[2]);
        };
        Vector<3> xyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[3]);
        };
        Vector<3> xzx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[0]);
        };
        Vector<3> xzy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[1]);
        };
        Vector<3> xzz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[2]);
        };
        Vector<3> xzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[3]);
        };
        Vector<3> xwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[0]);
        };
        Vector<3> xwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[1]);
        };
        Vector<3> xwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[2]);
        };
        Vector<3> xww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[3]);
        };

        Vector<4> xxxx() {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[0]);
        };
        Vector<4> xxxy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[1]);
        };
        Vector<4> xxxz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[2]);
        };
        Vector<4> xxxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[3]);
        };
        Vector<4> xxyx() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[0]);
        };
        Vector<4> xxyy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[1]);
        };
        Vector<4> xxyz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[2]);
        };
        Vector<4> xxyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[3]);
        };
        Vector<4> xxzx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[0]);
        };
        Vector<4> xxzy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[1]);
        };
        Vector<4> xxzz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[2]);
        };
        Vector<4> xxzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[3]);
        };
        Vector<4> xxwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[0]);
        };
        Vector<4> xxwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[1]);
        };
        Vector<4> xxwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[2]);
        };
        Vector<4> xxww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[3]);
        };
        Vector<4> xyxx() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[0]);
        };
        Vector<4> xyxy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[1]);
        };
        Vector<4> xyxz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[2]);
        };
        Vector<4> xyxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[3]);
        };
        Vector<4> xyyx() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[0]);
        };
        Vector<4> xyyy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[1]);
        };
        Vector<4> xyyz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[2]);
        };
        Vector<4> xyyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[3]);
        };
        Vector<4> xyzx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[0]);
        };
        Vector<4> xyzy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[1]);
        };
        Vector<4> xyzz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[2]);
        };
        Vector<4> xyzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[3]);
        };
        Vector<4> xywx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[0]);
        };
        Vector<4> xywy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[1]);
        };
        Vector<4> xywz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[2]);
        };
        Vector<4> xyww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[3]);
        };
        Vector<4> xzxx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[0]);
        };
        Vector<4> xzxy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[1]);
        };
        Vector<4> xzxz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[2]);
        };
        Vector<4> xzxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[3]);
        };
        Vector<4> xzyx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[0]);
        };
        Vector<4> xzyy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[1]);
        };
        Vector<4> xzyz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[2]);
        };
        Vector<4> xzyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[3]);
        };
        Vector<4> xzzx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[0]);
        };
        Vector<4> xzzy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[1]);
        };
        Vector<4> xzzz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[2]);
        };
        Vector<4> xzzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[3]);
        };
        Vector<4> xzwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[0]);
        };
        Vector<4> xzwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[1]);
        };
        Vector<4> xzwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[2]);
        };
        Vector<4> xzww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[3]);
        };
        Vector<4> xwxx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[0]);
        };
        Vector<4> xwxy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[1]);
        };
        Vector<4> xwxz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[2]);
        };
        Vector<4> xwxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[3]);
        };
        Vector<4> xwyx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[0]);
        };
        Vector<4> xwyy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[1]);
        };
        Vector<4> xwyz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[2]);
        };
        Vector<4> xwyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[3]);
        };
        Vector<4> xwzx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[0]);
        };
        Vector<4> xwzy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[1]);
        };
        Vector<4> xwzz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[2]);
        };
        Vector<4> xwzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[3]);
        };
        Vector<4> xwwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[0]);
        };
        Vector<4> xwwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[1]);
        };
        Vector<4> xwwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[2]);
        };
        Vector<4> xwww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[3]);
        };

        float y() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return _data[1];
        };
        Vector<1> y() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<1>(_data[1]);
        };
        Vector<2> yx() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<2>(_data[1], _data[0]);
        };
        Vector<2> yz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[1], _data[2]);
        };
        Vector<2> yw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[1], _data[3]);
        };
        Vector<2> yy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<2>(_data[1], _data[1]);
        };
        Vector<3> yxx() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[0]);
        };
        Vector<3> yxy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[1]);
        };
        Vector<3> yxz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[2]);
        };
        Vector<3> yxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[3]);
        };
        Vector<3> yyx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[0]);
        };
        Vector<3> yyy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[1]);
        };
        Vector<3> yyz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[2]);
        };
        Vector<3> yyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[3]);
        };
        Vector<3> yzx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[0]);
        };
        Vector<3> yzy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[1]);
        };
        Vector<3> yzz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[2]);
        };
        Vector<3> yzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[3]);
        };
        Vector<3> ywx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[0]);
        };
        Vector<3> ywy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[1]);
        };
        Vector<3> ywz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[2]);
        };
        Vector<3> yww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[3]);
        };
        Vector<4> yxxx() {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[0]);
        };
        Vector<4> yxxy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[1]);
        };
        Vector<4> yxxz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[2]);
        };
        Vector<4> yxxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[3]);
        };
        Vector<4> yxyx() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[0]);
        };
        Vector<4> yxyy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[1]);
        };
        Vector<4> yxyz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[2]);
        };
        Vector<4> yxyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[3]);
        };
        Vector<4> yxzx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[0]);
        };
        Vector<4> yxzy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[1]);
        };
        Vector<4> yxzz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[2]);
        };
        Vector<4> yxzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[3]);
        };
        Vector<4> yxwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[0]);
        };
        Vector<4> yxwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[1]);
        };
        Vector<4> yxwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[2]);
        };
        Vector<4> yxww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[3]);
        };
        Vector<4> yyxx() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[0]);
        };
        Vector<4> yyxy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[1]);
        };
        Vector<4> yyxz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[2]);
        };
        Vector<4> yyxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[3]);
        };
        Vector<4> yyyx() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[0]);
        };
        Vector<4> yyyy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[1]);
        };
        Vector<4> yyyz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[2]);
        };
        Vector<4> yyyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[3]);
        };
        Vector<4> yyzx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[0]);
        };
        Vector<4> yyzy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[1]);
        };
        Vector<4> yyzz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[2]);
        };
        Vector<4> yyzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[3]);
        };
        Vector<4> yywx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[0]);
        };
        Vector<4> yywy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[1]);
        };
        Vector<4> yywz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[2]);
        };
        Vector<4> yyww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[3]);
        };
        Vector<4> yzxx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[0]);
        };
        Vector<4> yzxy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[1]);
        };
        Vector<4> yzxz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[2]);
        };
        Vector<4> yzxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[3]);
        };
        Vector<4> yzyx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[0]);
        };
        Vector<4> yzyy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[1]);
        };
        Vector<4> yzyz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[2]);
        };
        Vector<4> yzyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[3]);
        };
        Vector<4> yzzx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[0]);
        };
        Vector<4> yzzy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[1]);
        };
        Vector<4> yzzz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[2]);
        };
        Vector<4> yzzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[3]);
        };
        Vector<4> yzwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[0]);
        };
        Vector<4> yzwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[1]);
        };
        Vector<4> yzwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[2]);
        };
        Vector<4> yzww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[3]);
        };
        Vector<4> ywxx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[0]);
        };
        Vector<4> ywxy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[1]);
        };
        Vector<4> ywxz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[2]);
        };
        Vector<4> ywxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[3]);
        };
        Vector<4> ywyx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[0]);
        };
        Vector<4> ywyy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[1]);
        };
        Vector<4> ywyz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[2]);
        };
        Vector<4> ywyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[3]);
        };
        Vector<4> ywzx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[0]);
        };
        Vector<4> ywzy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[1]);
        };
        Vector<4> ywzz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[2]);
        };
        Vector<4> ywzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[3]);
        };
        Vector<4> ywwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[0]);
        };
        Vector<4> ywwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[1]);
        };
        Vector<4> ywwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[2]);
        };
        Vector<4> ywww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[3]);
        };

        float z() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return _data[2];
        };
        Vector<1> z() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<1>(_data[2]);
        };
        Vector<2> zx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[2], _data[0]);
        };
        Vector<2> zy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[2], _data[1]);
        };
        Vector<2> zz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[2], _data[2]);
        };
        Vector<2> zw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[2], _data[3]);
        };
        Vector<3> zxx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[0]);
        };
        Vector<3> zxy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[1]);
        };
        Vector<3> zxz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[2]);
        };
        Vector<3> zxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[3]);
        };
        Vector<3> zyx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[0]);
        };
        Vector<3> zyy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[1]);
        };
        Vector<3> zyz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[2]);
        };
        Vector<3> zyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[3]);
        };
        Vector<3> zzx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[0]);
        };
        Vector<3> zzy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[1]);
        };
        Vector<3> zzz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[2]);
        };
        Vector<3> zzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[3]);
        };
        Vector<3> zwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[0]);
        };
        Vector<3> zwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[1]);
        };
        Vector<3> zwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[2]);
        };
        Vector<3> zww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[3]);
        };
        Vector<4> zxxx() {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[0]);
        };
        Vector<4> zxxy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[1]);
        };
        Vector<4> zxxz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[2]);
        };
        Vector<4> zxxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[3]);
        };
        Vector<4> zxyx() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[0]);
        };
        Vector<4> zxyy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[1]);
        };
        Vector<4> zxyz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[2]);
        };
        Vector<4> zxyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[3]);
        };
        Vector<4> zxzx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[0]);
        };
        Vector<4> zxzy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[1]);
        };
        Vector<4> zxzz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[2]);
        };
        Vector<4> zxzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[3]);
        };
        Vector<4> zxwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[0]);
        };
        Vector<4> zxwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[1]);
        };
        Vector<4> zxwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[2]);
        };
        Vector<4> zxww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[3]);
        };
        Vector<4> zyxx() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[0]);
        };
        Vector<4> zyxy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[1]);
        };
        Vector<4> zyxz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[2]);
        };
        Vector<4> zyxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[3]);
        };
        Vector<4> zyyx() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[0]);
        };
        Vector<4> zyyy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[1]);
        };
        Vector<4> zyyz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[2]);
        };
        Vector<4> zyyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[3]);
        };
        Vector<4> zyzx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[0]);
        };
        Vector<4> zyzy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[1]);
        };
        Vector<4> zyzz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[2]);
        };
        Vector<4> zyzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[3]);
        };
        Vector<4> zywx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[0]);
        };
        Vector<4> zywy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[1]);
        };
        Vector<4> zywz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[2]);
        };
        Vector<4> zyww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[3]);
        };
        Vector<4> zzxx() {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[0]);
        };
        Vector<4> zzxy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[1]);
        };
        Vector<4> zzxz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[2]);
        };
        Vector<4> zzxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[3]);
        };
        Vector<4> zzyx() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[0]);
        };
        Vector<4> zzyy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[1]);
        };
        Vector<4> zzyz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[2]);
        };
        Vector<4> zzyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[3]);
        };
        Vector<4> zzzx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[0]);
        };
        Vector<4> zzzy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[1]);
        };
        Vector<4> zzzz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[2]);
        };
        Vector<4> zzzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[3]);
        };
        Vector<4> zzwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[0]);
        };
        Vector<4> zzwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[1]);
        };
        Vector<4> zzwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[2]);
        };
        Vector<4> zzww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[3]);
        };
        Vector<4> zwxx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[0]);
        };
        Vector<4> zwxy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[1]);
        };
        Vector<4> zwxz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[2]);
        };
        Vector<4> zwxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[3]);
        };
        Vector<4> zwyx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[0]);
        };
        Vector<4> zwyy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[1]);
        };
        Vector<4> zwyz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[2]);
        };
        Vector<4> zwyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[3]);
        };
        Vector<4> zwzx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[0]);
        };
        Vector<4> zwzy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[1]);
        };
        Vector<4> zwzz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[2]);
        };
        Vector<4> zwzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[3]);
        };
        Vector<4> zwwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[0]);
        };
        Vector<4> zwwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[1]);
        };
        Vector<4> zwwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[2]);
        };
        Vector<4> zwww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[3]);
        };

        float w() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return _data[3];
        };
        Vector<1> w() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<1>(_data[3]);
        };
        Vector<2> wx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[3], _data[0]);
        };
        Vector<2> wy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[3], _data[1]);
        };
        Vector<2> wz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[3], _data[2]);
        };
        Vector<3> wxx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[0]);
        };
        Vector<3> wxy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[1]);
        };
        Vector<3> wxz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[2]);
        };
        Vector<3> wxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[3]);
        };
        Vector<3> wyx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[0]);
        };
        Vector<3> wyy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[1]);
        };
        Vector<3> wyz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[2]);
        };
        Vector<3> wyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[3]);
        };
        Vector<3> wzx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[0]);
        };
        Vector<3> wzy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[1]);
        };
        Vector<3> wzz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[2]);
        };
        Vector<3> wzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[3]);
        };
        Vector<3> wwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[0]);
        };
        Vector<3> wwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[1]);
        };
        Vector<3> wwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[2]);
        };
        Vector<3> www() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[3]);
        };
        Vector<4> wxxx() {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[0]);
        };
        Vector<4> wxxy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[1]);
        };
        Vector<4> wxxz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[2]);
        };
        Vector<4> wxxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[3]);
        };
        Vector<4> wxyx() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[0]);
        };
        Vector<4> wxyy() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[1]);
        };
        Vector<4> wxyz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[2]);
        };
        Vector<4> wxyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[3]);
        };
        Vector<4> wxzx() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[0]);
        };
        Vector<4> wxzy() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[1]);
        };
        Vector<4> wxzz() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[2]);
        };
        Vector<4> wxzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[3]);
        };
        Vector<4> wxwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[0]);
        };
        Vector<4> wxwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[1]);
        };
        Vector<4> wxwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[2]);
        };
        Vector<4> wxww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[3]);
        };
        Vector<4> wyxx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[0]);
        };
        Vector<4> wyxy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[1]);
        };
        Vector<4> wyxz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[2]);
        };
        Vector<4> wyxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[3]);
        };
        Vector<4> wyyx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[0]);
        };
        Vector<4> wyyy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[1]);
        };
        Vector<4> wyyz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[2]);
        };
        Vector<4> wyyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[3]);
        };
        Vector<4> wyzx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[0]);
        };
        Vector<4> wyzy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[1]);
        };
        Vector<4> wyzz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[2]);
        };
        Vector<4> wyzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[3]);
        };
        Vector<4> wywx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[0]);
        };
        Vector<4> wywy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[1]);
        };
        Vector<4> wywz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[2]);
        };
        Vector<4> wyww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[3]);
        };
        Vector<4> wzxx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[0]);
        };
        Vector<4> wzxy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[1]);
        };
        Vector<4> wzxz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[2]);
        };
        Vector<4> wzxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[3]);
        };
        Vector<4> wzyx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[0]);
        };
        Vector<4> wzyy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[1]);
        };
        Vector<4> wzyz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[2]);
        };
        Vector<4> wzyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[3]);
        };
        Vector<4> wzzx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[0]);
        };
        Vector<4> wzzy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[1]);
        };
        Vector<4> wzzz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[2]);
        };
        Vector<4> wzzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[3]);
        };
        Vector<4> wzwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[0]);
        };
        Vector<4> wzwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[1]);
        };
        Vector<4> wzwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[2]);
        };
        Vector<4> wzww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[3]);
        };
        Vector<4> wwxx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[0]);
        };
        Vector<4> wwxy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[1]);
        };
        Vector<4> wwxz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[2]);
        };
        Vector<4> wwxw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[3]);
        };
        Vector<4> wwyx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[0]);
        };
        Vector<4> wwyy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[1]);
        };
        Vector<4> wwyz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[2]);
        };
        Vector<4> wwyw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[3]);
        };
        Vector<4> wwzx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[0]);
        };
        Vector<4> wwzy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[1]);
        };
        Vector<4> wwzz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[2]);
        };
        Vector<4> wwzw() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[3]);
        };
        Vector<4> wwwx() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[0]);
        };
        Vector<4> wwwy() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[1]);
        };
        Vector<4> wwwz() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[2]);
        };
        Vector<4> wwww() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[3]);
        };

        float r() const {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return _data[0];
        };
        Vector<1> r() {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<1>(_data[0]);
        };
        Vector<2> rr() {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<2>(_data[0], _data[0]);
        };
        Vector<2> rg() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<2>(_data[0], _data[1]);
        };
        Vector<2> rb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[0], _data[2]);
        };
        Vector<2> ra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[0], _data[3]);
        };
        Vector<3> rrr() {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[0]);
        };
        Vector<3> rrg() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[1]);
        };
        Vector<3> rrb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[2]);
        };
        Vector<3> rra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[3]);
        };
        Vector<3> rgr() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[0]);
        };
        Vector<3> rgg() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[1]);
        };
        Vector<3> rgb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[2]);
        };
        Vector<3> rga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[3]);
        };
        Vector<3> rbr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[0]);
        };
        Vector<3> rbg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[1]);
        };
        Vector<3> rbb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[2]);
        };
        Vector<3> rba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[3]);
        };
        Vector<3> rar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[0]);
        };
        Vector<3> rag() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[1]);
        };
        Vector<3> rab() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[2]);
        };
        Vector<3> raa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[3]);
        };
        Vector<4> rrrr() {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[0]);
        };
        Vector<4> rrrg() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[1]);
        };
        Vector<4> rrrb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[2]);
        };
        Vector<4> rrra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[3]);
        };
        Vector<4> rrgr() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[0]);
        };
        Vector<4> rrgg() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[1]);
        };
        Vector<4> rrgb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[2]);
        };
        Vector<4> rrga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[3]);
        };
        Vector<4> rrbr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[0]);
        };
        Vector<4> rrbg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[1]);
        };
        Vector<4> rrbb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[2]);
        };
        Vector<4> rrba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[3]);
        };
        Vector<4> rrar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[0]);
        };
        Vector<4> rrag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[1]);
        };
        Vector<4> rrab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[2]);
        };
        Vector<4> rraa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[3]);
        };
        Vector<4> rgrr() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[0]);
        };
        Vector<4> rgrg() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[1]);
        };
        Vector<4> rgrb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[2]);
        };
        Vector<4> rgra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[3]);
        };
        Vector<4> rggr() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[0]);
        };
        Vector<4> rggg() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[1]);
        };
        Vector<4> rggb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[2]);
        };
        Vector<4> rgga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[3]);
        };
        Vector<4> rgbr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[0]);
        };
        Vector<4> rgbg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[1]);
        };
        Vector<4> rgbb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[2]);
        };
        Vector<4> rgba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[3]);
        };
        Vector<4> rgar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[0]);
        };
        Vector<4> rgag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[1]);
        };
        Vector<4> rgab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[2]);
        };
        Vector<4> rgaa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[3]);
        };
        Vector<4> rbrr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[0]);
        };
        Vector<4> rbrg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[1]);
        };
        Vector<4> rbrb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[2]);
        };
        Vector<4> rbra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[3]);
        };
        Vector<4> rbgr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[0]);
        };
        Vector<4> rbgg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[1]);
        };
        Vector<4> rbgb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[2]);
        };
        Vector<4> rbga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[3]);
        };
        Vector<4> rbbr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[0]);
        };
        Vector<4> rbbg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[1]);
        };
        Vector<4> rbbb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[2]);
        };
        Vector<4> rbba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[3]);
        };
        Vector<4> rbar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[0]);
        };
        Vector<4> rbag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[1]);
        };
        Vector<4> rbab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[2]);
        };
        Vector<4> rbaa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[3]);
        };
        Vector<4> rarr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[0]);
        };
        Vector<4> rarg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[1]);
        };
        Vector<4> rarb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[2]);
        };
        Vector<4> rara() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[3]);
        };
        Vector<4> ragr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[0]);
        };
        Vector<4> ragg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[1]);
        };
        Vector<4> ragb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[2]);
        };
        Vector<4> raga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[3]);
        };
        Vector<4> rabr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[0]);
        };
        Vector<4> rabg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[1]);
        };
        Vector<4> rabb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[2]);
        };
        Vector<4> raba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[3]);
        };
        Vector<4> raar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[0]);
        };
        Vector<4> raag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[1]);
        };
        Vector<4> raab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[2]);
        };
        Vector<4> raaa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[3]);
        };

        float g() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return _data[1];
        };
        Vector<1> g() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<1>(_data[1]);
        };
        Vector<2> gr() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<2>(_data[1], _data[0]);
        };
        Vector<2> gg() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<2>(_data[1], _data[1]);
        };
        Vector<2> gb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[1], _data[2]);
        };
        Vector<2> ga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[1], _data[3]);
        };
        Vector<3> grr() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[0]);
        };
        Vector<3> grg() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[1]);
        };
        Vector<3> grb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[2]);
        };
        Vector<3> gra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[3]);
        };
        Vector<3> ggr() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[0]);
        };
        Vector<3> ggg() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[1]);
        };
        Vector<3> ggb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[2]);
        };
        Vector<3> gga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[3]);
        };
        Vector<3> gbr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[0]);
        };
        Vector<3> gbg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[1]);
        };
        Vector<3> gbb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[2]);
        };
        Vector<3> gba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[3]);
        };
        Vector<3> gar() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[0]);
        };
        Vector<3> gag() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[1]);
        };
        Vector<3> gab() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[2]);
        };
        Vector<3> gaa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[3]);
        };
        Vector<4> grrr() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[0]);
        };
        Vector<4> grrg() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[1]);
        };
        Vector<4> grrb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[2]);
        };
        Vector<4> grra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[3]);
        };
        Vector<4> grgr() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[0]);
        };
        Vector<4> grgg() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[1]);
        };
        Vector<4> grgb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[2]);
        };
        Vector<4> grga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[3]);
        };
        Vector<4> grbr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[0]);
        };
        Vector<4> grbg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[1]);
        };
        Vector<4> grbb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[2]);
        };
        Vector<4> grba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[3]);
        };
        Vector<4> grar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[0]);
        };
        Vector<4> grag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[1]);
        };
        Vector<4> grab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[2]);
        };
        Vector<4> graa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[3]);
        };
        Vector<4> ggrr() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[0]);
        };
        Vector<4> ggrg() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[1]);
        };
        Vector<4> ggrb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[2]);
        };
        Vector<4> ggra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[3]);
        };
        Vector<4> gggr() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[0]);
        };
        Vector<4> gggg() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[1]);
        };
        Vector<4> gggb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[2]);
        };
        Vector<4> ggga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[3]);
        };
        Vector<4> ggbr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[0]);
        };
        Vector<4> ggbg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[1]);
        };
        Vector<4> ggbb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[2]);
        };
        Vector<4> ggba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[3]);
        };
        Vector<4> ggar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[0]);
        };
        Vector<4> ggag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[1]);
        };
        Vector<4> ggab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[2]);
        };
        Vector<4> ggaa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[3]);
        };
        Vector<4> gbrr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[0]);
        };
        Vector<4> gbrg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[1]);
        };
        Vector<4> gbrb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[2]);
        };
        Vector<4> gbra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[3]);
        };
        Vector<4> gbgr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[0]);
        };
        Vector<4> gbgg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[1]);
        };
        Vector<4> gbgb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[2]);
        };
        Vector<4> gbga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[3]);
        };
        Vector<4> gbbr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[0]);
        };
        Vector<4> gbbg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[1]);
        };
        Vector<4> gbbb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[2]);
        };
        Vector<4> gbba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[3]);
        };
        Vector<4> gbar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[0]);
        };
        Vector<4> gbag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[1]);
        };
        Vector<4> gbab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[2]);
        };
        Vector<4> gbaa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[3]);
        };
        Vector<4> garr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[0]);
        };
        Vector<4> garg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[1]);
        };
        Vector<4> garb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[2]);
        };
        Vector<4> gara() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[3]);
        };
        Vector<4> gagr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[0]);
        };
        Vector<4> gagg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[1]);
        };
        Vector<4> gagb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[2]);
        };
        Vector<4> gaga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[3]);
        };
        Vector<4> gabr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[0]);
        };
        Vector<4> gabg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[1]);
        };
        Vector<4> gabb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[2]);
        };
        Vector<4> gaba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[3]);
        };
        Vector<4> gaar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[0]);
        };
        Vector<4> gaag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[1]);
        };
        Vector<4> gaab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[2]);
        };
        Vector<4> gaaa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[3]);
        };

        float b() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return _data[2];
        };
        Vector<1> b() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<1>(_data[2]);
        };
        Vector<2> br() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[2], _data[0]);
        };
        Vector<2> bg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[2], _data[1]);
        };
        Vector<2> bb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[2], _data[2]);
        };
        Vector<2> ba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[2], _data[3]);
        };
        Vector<3> brr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[0]);
        };
        Vector<3> brg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[1]);
        };
        Vector<3> brb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[2]);
        };
        Vector<3> bra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[3]);
        };
        Vector<3> bgr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[0]);
        };
        Vector<3> bgg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[1]);
        };
        Vector<3> bgb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[2]);
        };
        Vector<3> bga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[3]);
        };
        Vector<3> bbr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[0]);
        };
        Vector<3> bbg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[1]);
        };
        Vector<3> bbb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[2]);
        };
        Vector<3> bba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[3]);
        };
        Vector<3> bar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[0]);
        };
        Vector<3> bag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[1]);
        };
        Vector<3> bab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[2]);
        };
        Vector<3> baa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[3]);
        };
        Vector<4> brrr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[0]);
        };
        Vector<4> brrg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[1]);
        };
        Vector<4> brrb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[2]);
        };
        Vector<4> brra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[3]);
        };
        Vector<4> brgr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[0]);
        };
        Vector<4> brgg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[1]);
        };
        Vector<4> brgb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[2]);
        };
        Vector<4> brga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[3]);
        };
        Vector<4> brbr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[0]);
        };
        Vector<4> brbg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[1]);
        };
        Vector<4> brbb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[2]);
        };
        Vector<4> brba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[3]);
        };
        Vector<4> brar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[0]);
        };
        Vector<4> brag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[1]);
        };
        Vector<4> brab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[2]);
        };
        Vector<4> braa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[3]);
        };
        Vector<4> bgrr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[0]);
        };
        Vector<4> bgrg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[1]);
        };
        Vector<4> bgrb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[2]);
        };
        Vector<4> bgra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[3]);
        };
        Vector<4> bggr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[0]);
        };
        Vector<4> bggg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[1]);
        };
        Vector<4> bggb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[2]);
        };
        Vector<4> bgga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[3]);
        };
        Vector<4> bgbr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[0]);
        };
        Vector<4> bgbg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[1]);
        };
        Vector<4> bgbb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[2]);
        };
        Vector<4> bgba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[3]);
        };
        Vector<4> bgar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[0]);
        };
        Vector<4> bgag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[1]);
        };
        Vector<4> bgab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[2]);
        };
        Vector<4> bgaa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[3]);
        };
        Vector<4> bbrr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[0]);
        };
        Vector<4> bbrg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[1]);
        };
        Vector<4> bbrb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[2]);
        };
        Vector<4> bbra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[3]);
        };
        Vector<4> bbgr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[0]);
        };
        Vector<4> bbgg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[1]);
        };
        Vector<4> bbgb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[2]);
        };
        Vector<4> bbga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[3]);
        };
        Vector<4> bbbr() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[0]);
        };
        Vector<4> bbbg() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[1]);
        };
        Vector<4> bbbb() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[2]);
        };
        Vector<4> bbba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[3]);
        };
        Vector<4> bbar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[0]);
        };
        Vector<4> bbag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[1]);
        };
        Vector<4> bbab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[2]);
        };
        Vector<4> bbaa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[3]);
        };
        Vector<4> barr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[0]);
        };
        Vector<4> barg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[1]);
        };
        Vector<4> barb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[2]);
        };
        Vector<4> bara() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[3]);
        };
        Vector<4> bagr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[0]);
        };
        Vector<4> bagg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[1]);
        };
        Vector<4> bagb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[2]);
        };
        Vector<4> baga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[3]);
        };
        Vector<4> babr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[0]);
        };
        Vector<4> babg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[1]);
        };
        Vector<4> babb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[2]);
        };
        Vector<4> baba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[3]);
        };
        Vector<4> baar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[0]);
        };
        Vector<4> baag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[1]);
        };
        Vector<4> baab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[2]);
        };
        Vector<4> baaa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[3]);
        };

        float a() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return _data[3];
        };
        Vector<1> a() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<1>(_data[3]);
        };
        Vector<2> ar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[3], _data[0]);
        };
        Vector<2> ag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[3], _data[1]);
        };
        Vector<2> ab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[3], _data[2]);
        };
        Vector<2> aa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[3], _data[3]);
        };
        Vector<3> arr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[0]);
        };
        Vector<3> arg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[1]);
        };
        Vector<3> arb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[2]);
        };
        Vector<3> ara() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[3]);
        };
        Vector<3> agr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[0]);
        };
        Vector<3> agg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[1]);
        };
        Vector<3> agb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[2]);
        };
        Vector<3> aga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[3]);
        };
        Vector<3> abr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[0]);
        };
        Vector<3> abg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[1]);
        };
        Vector<3> abb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[2]);
        };
        Vector<3> aba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[3]);
        };
        Vector<3> aar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[0]);
        };
        Vector<3> aag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[1]);
        };
        Vector<3> aab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[2]);
        };
        Vector<3> aaa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[3]);
        };
        Vector<4> arrr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[0]);
        };
        Vector<4> arrg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[1]);
        };
        Vector<4> arrb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[2]);
        };
        Vector<4> arra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[3]);
        };
        Vector<4> argr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[0]);
        };
        Vector<4> argg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[1]);
        };
        Vector<4> argb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[2]);
        };
        Vector<4> arga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[3]);
        };
        Vector<4> arbr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[0]);
        };
        Vector<4> arbg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[1]);
        };
        Vector<4> arbb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[2]);
        };
        Vector<4> arba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[3]);
        };
        Vector<4> arar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[0]);
        };
        Vector<4> arag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[1]);
        };
        Vector<4> arab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[2]);
        };
        Vector<4> araa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[3]);
        };
        Vector<4> agrr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[0]);
        };
        Vector<4> agrg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[1]);
        };
        Vector<4> agrb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[2]);
        };
        Vector<4> agra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[3]);
        };
        Vector<4> aggr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[0]);
        };
        Vector<4> aggg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[1]);
        };
        Vector<4> aggb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[2]);
        };
        Vector<4> agga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[3]);
        };
        Vector<4> agbr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[0]);
        };
        Vector<4> agbg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[1]);
        };
        Vector<4> agbb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[2]);
        };
        Vector<4> agba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[3]);
        };
        Vector<4> agar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[0]);
        };
        Vector<4> agag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[1]);
        };
        Vector<4> agab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[2]);
        };
        Vector<4> agaa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[3]);
        };
        Vector<4> abrr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[0]);
        };
        Vector<4> abrg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[1]);
        };
        Vector<4> abrb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[2]);
        };
        Vector<4> abra() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[3]);
        };
        Vector<4> abgr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[0]);
        };
        Vector<4> abgg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[1]);
        };
        Vector<4> abgb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[2]);
        };
        Vector<4> abga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[3]);
        };
        Vector<4> abbr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[0]);
        };
        Vector<4> abbg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[1]);
        };
        Vector<4> abbb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[2]);
        };
        Vector<4> abba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[3]);
        };
        Vector<4> abar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[0]);
        };
        Vector<4> abag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[1]);
        };
        Vector<4> abab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[2]);
        };
        Vector<4> abaa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[3]);
        };
        Vector<4> aarr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[0]);
        };
        Vector<4> aarg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[1]);
        };
        Vector<4> aarb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[2]);
        };
        Vector<4> aara() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[3]);
        };
        Vector<4> aagr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[0]);
        };
        Vector<4> aagg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[1]);
        };
        Vector<4> aagb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[2]);
        };
        Vector<4> aaga() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[3]);
        };
        Vector<4> aabr() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[0]);
        };
        Vector<4> aabg() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[1]);
        };
        Vector<4> aabb() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[2]);
        };
        Vector<4> aaba() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[3]);
        };
        Vector<4> aaar() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[0]);
        };
        Vector<4> aaag() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[1]);
        };
        Vector<4> aaab() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[2]);
        };
        Vector<4> aaaa() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[3]);
        };
    };
}
