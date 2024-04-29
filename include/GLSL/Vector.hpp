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
    template <std::size_t N>
    class Vector {
    protected:
        double _data[N]{};
    public:
        Vector() {
            for (std::size_t i = 0; i < N; i++) {
                _data[i] = 0.0;
            }
        };
        explicit Vector(double value, ...) {
            va_list args;
            _data[0] = value;
            va_start(args, value);
            for (std::size_t i = 1; i < N; i++) {
                _data[i] = va_arg(args, double);
            }
            va_end(args);
        };
        Vector(const Vector &other) {
            for (std::size_t i = 0; i < N; i++) {
                _data[i] = other[i];
            }
        };
        ~Vector() = default;

        [[nodiscard]] double length() const {
            double sum = 0;
            for (std::size_t i = 0; i < N; i++) {
                sum += _data[i] * _data[i];
            }
            return sqrt(sum);
        };
        [[nodiscard]] double dot(const Vector &other) const {
            double sum = 0;
            for (std::size_t i = 0; i < N; i++) {
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

        Vector &operator=(const Vector &other) {
            if (this == &other) {
                return *this;
            }
            for (std::size_t i = 0; i < N; i++) {
                _data[i] = other[i];
            }
            return *this;
        };

        bool operator==(const Vector &other) const {
            for (std::size_t i = 0; i < N; i++) {
                if (_data[i] != other[i]) {
                    return false;
                }
            }
            return true;
        };
        bool operator!=(const Vector &other) const {
            return !(*this == other);
        };

        Vector operator+(const Vector &other) const {
            Vector result;
            for (std::size_t i = 0; i < N; i++) {
                result[i] = _data[i] + other[i];
            }
            return result;
        };
        Vector operator-(const Vector &other) const {
            Vector result;
            for (std::size_t i = 0; i < N; i++) {
                result[i] = _data[i] - other[i];
            }
            return result;
        };
        Vector operator*(const Vector &other) const {
            Vector result;
            for (std::size_t i = 0; i < N; ++i) {
                std::size_t next_i = (i + 1) % N;
                std::size_t prev_i = (i - 1 + N) % N;
                result[i] = _data[next_i] * other[prev_i] - _data[prev_i] * other[next_i];
            }
            return result;
        };
        Vector operator/(const Vector &other) const {
            Vector result;
            for (size_t i = 0; i < N; ++i) {
                if (other[i] == 0) {
                    throw std::invalid_argument("Division by zero");
                }
                result[i] = _data[i] / other[i];
            }
            return result;
        };
        Vector operator*(double scalar) const {
            Vector result;
            for (std::size_t i = 0; i < N; i++) {
                result[i] = _data[i] * scalar;
            }
            return result;
        };
        Vector operator/(double scalar) const {
            Vector result;
            for (std::size_t i = 0; i < N; i++) {
                result[i] = _data[i] / scalar;
            }
            return result;
        };
        Vector operator-(double scalar) const {
            Vector result;
            for (std::size_t i = 0; i < N; i++) {
                result[i] = _data[i] - scalar;
            }
            return result;
        };
        Vector operator+(double scalar) const {
            Vector result;
            for (std::size_t i = 0; i < N; i++) {
                result[i] = _data[i] + scalar;
            }
            return result;
        };
        Vector operator-() const {
            Vector result;
            for (std::size_t i = 0; i < N; i++) {
                result[i] = -_data[i];
            }
            return result;
        };

        Vector &operator+=(const Vector &other) {
            *this = *this + other;
            return *this;
        };

        Vector &operator-=(const Vector &other) {
            *this = *this - other;
            return *this;
        };

        Vector &operator*=(const Vector &other) {
            *this = *this * other;
            return *this;
        };

        Vector &operator/=(const Vector &other) {
            *this = *this / other;
            return *this;
        };

        Vector &operator+=(double scalar) {
            *this = *this + scalar;
            return *this;
        };

        Vector &operator-=(double scalar) {
            *this = *this - scalar;
            return *this;
        };

        Vector &operator*=(double scalar) {
            *this = *this * scalar;
            return *this;
        };

        Vector &operator/=(double scalar) {
            *this = *this / scalar;
            return *this;
        };

        [[nodiscard]] Vector normalize() const {
            return *this / length();
        };
        // Swizzling
        [[nodiscard]] double x() const {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimension");
            }
            return _data[0];
        };
        [[nodiscard]] double &x() {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimension");
            }
            return _data[0];
        };
        [[nodiscard]] Vector<2> xx() const {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<2>(_data[0], _data[0]);
        };
        [[nodiscard]] Vector<2> xy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<2>(_data[0], _data[1]);
        };
        [[nodiscard]] Vector<2> xz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[0], _data[2]);
        };
        [[nodiscard]] Vector<2> xw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[0], _data[3]);
        };
        [[nodiscard]] Vector<3> xxx() const {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<3> xxy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<3> xxz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<3> xxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<3> xyx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<3> xyy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<3> xyz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<3> xyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<3> xzx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<3> xzy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<3> xzz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<3> xzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<3> xwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<3> xwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<3> xwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<3> xww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[3]);
        };

        [[nodiscard]]Vector<4> xxxx() const {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> xxxy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> xxxz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> xxxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> xxyx() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> xxyy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> xxyz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> xxyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> xxzx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> xxzy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> xxzz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> xxzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> xxwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> xxwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> xxwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> xxww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> xyxx() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> xyxy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> xyxz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> xyxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> xyyx() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> xyyy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> xyyz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> xyyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> xyzx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> xyzy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> xyzz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> xyzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> xywx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> xywy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> xywz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> xyww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> xzxx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> xzxy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> xzxz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> xzxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> xzyx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> xzyy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> xzyz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> xzyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> xzzx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> xzzy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> xzzz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> xzzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> xzwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> xzwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> xzwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> xzww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> xwxx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> xwxy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> xwxz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> xwxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> xwyx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> xwyy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> xwyz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> xwyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> xwzx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> xwzy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> xwzz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> xwzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> xwwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> xwwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> xwwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> xwww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[3]);
        };
        [[nodiscard]] double y() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return _data[1];
        };
        [[nodiscard]] double &y() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return _data[1];
        };
        [[nodiscard]]Vector<2> yx() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<2>(_data[1], _data[0]);
        };
        [[nodiscard]]Vector<2> yz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[1], _data[2]);
        };
        [[nodiscard]]Vector<2> yw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[1], _data[3]);
        };
        [[nodiscard]]Vector<2> yy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<2>(_data[1], _data[1]);
        };
        [[nodiscard]]Vector<3> yxx() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<3> yxy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<3> yxz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<3> yxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<3> yyx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<3> yyy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<3> yyz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<3> yyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<3> yzx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<3> yzy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<3> yzz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<3> yzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<3> ywx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<3> ywy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<3> ywz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<3> yww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> yxxx() const {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> yxxy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> yxxz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> yxxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> yxyx() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> yxyy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> yxyz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> yxyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> yxzx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> yxzy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> yxzz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> yxzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> yxwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> yxwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> yxwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> yxww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> yyxx() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> yyxy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> yyxz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> yyxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> yyyx() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> yyyy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> yyyz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> yyyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> yyzx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> yyzy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> yyzz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> yyzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> yywx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> yywy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> yywz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> yyww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> yzxx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> yzxy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> yzxz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> yzxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> yzyx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> yzyy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> yzyz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> yzyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> yzzx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> yzzy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> yzzz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> yzzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> yzwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> yzwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> yzwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> yzww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> ywxx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> ywxy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> ywxz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> ywxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> ywyx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> ywyy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> ywyz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> ywyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> ywzx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> ywzy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> ywzz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> ywzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> ywwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> ywwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> ywwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> ywww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[3]);
        };
        [[nodiscard]] double z() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return _data[2];
        };
        [[nodiscard]] double &z() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return _data[2];
        };
        [[nodiscard]]Vector<2> zx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[2], _data[0]);
        };
        [[nodiscard]]Vector<2> zy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[2], _data[1]);
        };
        [[nodiscard]]Vector<2> zz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[2], _data[2]);
        };
        [[nodiscard]]Vector<2> zw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[2], _data[3]);
        };
        [[nodiscard]]Vector<3> zxx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<3> zxy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<3> zxz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<3> zxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<3> zyx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<3> zyy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<3> zyz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<3> zyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<3> zzx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<3> zzy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<3> zzz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<3> zzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<3> zwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<3> zwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<3> zwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<3> zww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> zxxx() const {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> zxxy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> zxxz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> zxxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> zxyx() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> zxyy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> zxyz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> zxyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> zxzx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> zxzy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> zxzz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> zxzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> zxwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> zxwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> zxwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> zxww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> zyxx() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> zyxy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> zyxz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> zyxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> zyyx() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> zyyy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> zyyz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> zyyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> zyzx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> zyzy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> zyzz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> zyzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> zywx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> zywy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> zywz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> zyww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> zzxx() const {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> zzxy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> zzxz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> zzxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> zzyx() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> zzyy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> zzyz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> zzyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> zzzx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> zzzy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> zzzz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> zzzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> zzwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> zzwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> zzwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> zzww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> zwxx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> zwxy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> zwxz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> zwxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> zwyx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> zwyy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> zwyz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> zwyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> zwzx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> zwzy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> zwzz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> zwzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> zwwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> zwwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> zwwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> zwww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[3]);
        };
        [[nodiscard]] double w() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return _data[3];
        };
        [[nodiscard]] double &w() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return _data[3];
        };
        [[nodiscard]]Vector<2> wx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[3], _data[0]);
        };
        [[nodiscard]]Vector<2> wy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[3], _data[1]);
        };
        [[nodiscard]]Vector<2> wz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[3], _data[2]);
        };
        [[nodiscard]]Vector<3> wxx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<3> wxy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<3> wxz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<3> wxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<3> wyx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<3> wyy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<3> wyz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<3> wyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<3> wzx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<3> wzy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<3> wzz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<3> wzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<3> wwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<3> wwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<3> wwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<3> www() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> wxxx() const {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> wxxy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> wxxz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> wxxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> wxyx() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> wxyy() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> wxyz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> wxyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> wxzx() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> wxzy() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> wxzz() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> wxzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> wxwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> wxwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> wxwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> wxww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> wyxx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> wyxy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> wyxz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> wyxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> wyyx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> wyyy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> wyyz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> wyyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> wyzx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> wyzy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> wyzz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> wyzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> wywx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> wywy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> wywz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> wyww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> wzxx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> wzxy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> wzxz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> wzxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> wzyx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> wzyy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> wzyz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> wzyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> wzzx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> wzzy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> wzzz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> wzzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> wzwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> wzwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> wzwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> wzww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> wwxx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> wwxy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> wwxz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> wwxw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> wwyx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> wwyy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> wwyz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> wwyw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> wwzx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> wwzy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> wwzz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> wwzw() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> wwwx() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> wwwy() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> wwwz() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> wwww() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[3]);
        };
        [[nodiscard]] double r() const {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return _data[0];
        };
        [[nodiscard]] double &r() {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return _data[0];
        };
        [[nodiscard]]Vector<2> rr() const {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<2>(_data[0], _data[0]);
        };
        [[nodiscard]]Vector<2> rg() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<2>(_data[0], _data[1]);
        };
        [[nodiscard]]Vector<2> rb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[0], _data[2]);
        };
        [[nodiscard]]Vector<2> ra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[0], _data[3]);
        };
        [[nodiscard]]Vector<3> rrr() const {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<3> rrg() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<3> rrb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<3> rra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<3> rgr() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<3> rgg() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<3> rgb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<3> rga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<3> rbr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<3> rbg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<3> rbb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<3> rba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<3> rar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<3> rag() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<3> rab() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<3> raa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[0], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> rrrr() const {
            if (N < 1) {
                throw std::invalid_argument("Vector must have at least 1 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> rrrg() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> rrrb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> rrra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> rrgr() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> rrgg() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> rrgb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> rrga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> rrbr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> rrbg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> rrbb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> rrba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> rrar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> rrag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> rrab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> rraa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[0], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> rgrr() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> rgrg() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> rgrb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> rgra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> rggr() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> rggg() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> rggb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> rgga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> rgbr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> rgbg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> rgbb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> rgba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> rgar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> rgag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> rgab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> rgaa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[1], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> rbrr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> rbrg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> rbrb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> rbra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> rbgr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> rbgg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> rbgb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> rbga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> rbbr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> rbbg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> rbbb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> rbba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> rbar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> rbag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> rbab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> rbaa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[2], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> rarr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> rarg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> rarb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> rara() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> ragr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> ragg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> ragb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> raga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> rabr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> rabg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> rabb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> raba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> raar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> raag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> raab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> raaa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[0], _data[3], _data[3], _data[3]);
        };
        [[nodiscard]] double g() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return _data[1];
        };
        [[nodiscard]] double &g() {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return _data[1];
        };
        [[nodiscard]]Vector<2> gr() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<2>(_data[1], _data[0]);
        };
        [[nodiscard]]Vector<2> gg() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<2>(_data[1], _data[1]);
        };
        [[nodiscard]]Vector<2> gb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[1], _data[2]);
        };
        [[nodiscard]]Vector<2> ga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[1], _data[3]);
        };
        [[nodiscard]]Vector<3> grr() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<3> grg() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<3> grb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<3> gra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<3> ggr() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<3> ggg() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<3> ggb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<3> gga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<3> gbr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<3> gbg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<3> gbb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<3> gba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<3> gar() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<3> gag() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<3> gab() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<3> gaa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[1], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> grrr() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> grrg() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> grrb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> grra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> grgr() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> grgg() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> grgb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> grga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> grbr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> grbg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> grbb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> grba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> grar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> grag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> grab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> graa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[0], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> ggrr() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> ggrg() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> ggrb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> ggra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> gggr() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> gggg() const {
            if (N < 2) {
                throw std::invalid_argument("Vector must have at least 2 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> gggb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> ggga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> ggbr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> ggbg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> ggbb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> ggba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> ggar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> ggag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> ggab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> ggaa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[1], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> gbrr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> gbrg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> gbrb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> gbra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> gbgr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> gbgg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> gbgb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> gbga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> gbbr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> gbbg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> gbbb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> gbba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> gbar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> gbag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> gbab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> gbaa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[2], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> garr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> garg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> garb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> gara() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> gagr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> gagg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> gagb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> gaga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> gabr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> gabg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> gabb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> gaba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> gaar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> gaag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> gaab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> gaaa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[1], _data[3], _data[3], _data[3]);
        };
        [[nodiscard]] double b() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return _data[2];
        };
        [[nodiscard]] double &b() {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return _data[2];
        };
        [[nodiscard]]Vector<2> br() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[2], _data[0]);
        };
        [[nodiscard]]Vector<2> bg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[2], _data[1]);
        };
        [[nodiscard]]Vector<2> bb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<2>(_data[2], _data[2]);
        };
        [[nodiscard]]Vector<2> ba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[2], _data[3]);
        };
        [[nodiscard]]Vector<3> brr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<3> brg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<3> brb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<3> bra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<3> bgr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<3> bgg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<3> bgb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<3> bga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<3> bbr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<3> bbg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<3> bbb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<3> bba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<3> bar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<3> bag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<3> bab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<3> baa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[2], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> brrr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> brrg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> brrb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> brra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> brgr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> brgg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> brgb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> brga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> brbr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> brbg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> brbb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> brba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> brar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> brag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> brab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> braa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[0], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> bgrr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> bgrg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> bgrb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> bgra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> bggr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> bggg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> bggb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> bgga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> bgbr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> bgbg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> bgbb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> bgba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> bgar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> bgag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> bgab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> bgaa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[1], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> bbrr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> bbrg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> bbrb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> bbra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> bbgr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> bbgg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> bbgb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> bbga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> bbbr() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> bbbg() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> bbbb() const {
            if (N < 3) {
                throw std::invalid_argument("Vector must have at least 3 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> bbba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> bbar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> bbag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> bbab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> bbaa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[2], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> barr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> barg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> barb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> bara() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> bagr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> bagg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> bagb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> baga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> babr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> babg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> babb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> baba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> baar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> baag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> baab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> baaa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[2], _data[3], _data[3], _data[3]);
        };
        [[nodiscard]] double a() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return _data[3];
        };
        [[nodiscard]] double &a() {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return _data[3];
        };
        [[nodiscard]]Vector<2> ar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[3], _data[0]);
        };
        [[nodiscard]]Vector<2> ag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[3], _data[1]);
        };
        [[nodiscard]]Vector<2> ab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[3], _data[2]);
        };
        [[nodiscard]]Vector<2> aa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<2>(_data[3], _data[3]);
        };
        [[nodiscard]]Vector<3> arr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<3> arg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<3> arb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<3> ara() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<3> agr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<3> agg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<3> agb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<3> aga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<3> abr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<3> abg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<3> abb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<3> aba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<3> aar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<3> aag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<3> aab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<3> aaa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<3>(_data[3], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> arrr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> arrg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> arrb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> arra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> argr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> argg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> argb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> arga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> arbr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> arbg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> arbb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> arba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> arar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> arag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> arab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> araa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[0], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> agrr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> agrg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> agrb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> agra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> aggr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> aggg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> aggb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> agga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> agbr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> agbg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> agbb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> agba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> agar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> agag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> agab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> agaa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[1], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> abrr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> abrg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> abrb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> abra() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> abgr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> abgg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> abgb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> abga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> abbr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> abbg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> abbb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> abba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> abar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> abag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> abab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> abaa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[2], _data[3], _data[3]);
        };
        [[nodiscard]]Vector<4> aarr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[0]);
        };
        [[nodiscard]]Vector<4> aarg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[1]);
        };
        [[nodiscard]]Vector<4> aarb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[2]);
        };
        [[nodiscard]]Vector<4> aara() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[0], _data[3]);
        };
        [[nodiscard]]Vector<4> aagr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[0]);
        };
        [[nodiscard]]Vector<4> aagg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[1]);
        };
        [[nodiscard]]Vector<4> aagb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[2]);
        };
        [[nodiscard]]Vector<4> aaga() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[1], _data[3]);
        };
        [[nodiscard]]Vector<4> aabr() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[0]);
        };
        [[nodiscard]]Vector<4> aabg() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[1]);
        };
        [[nodiscard]]Vector<4> aabb() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[2]);
        };
        [[nodiscard]]Vector<4> aaba() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[2], _data[3]);
        };
        [[nodiscard]]Vector<4> aaar() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[0]);
        };
        [[nodiscard]]Vector<4> aaag() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[1]);
        };
        [[nodiscard]]Vector<4> aaab() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[2]);
        };
        [[nodiscard]]Vector<4> aaaa() const {
            if (N < 4) {
                throw std::invalid_argument("Vector must have at least 4 dimensions");
            }
            return Vector<4>(_data[3], _data[3], _data[3], _data[3]);
        };
    };
}
