/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "GLSL/Vector.hpp"
#include <stdexcept>
#include <cmath>
#include <cstdarg>

namespace GLSL {
    template <std::size_t HEIGHT, std::size_t WIDTH>
    class Matrix {
    private:
        Vector<WIDTH> _matrix[HEIGHT];
    public:
        Matrix() {
            for (std::size_t i = 0; i < HEIGHT; i++) {
                _matrix[i] = Vector<WIDTH>();
            }
        }
        explicit Matrix(double a11, ...) {
            va_list args;
            va_start(args, a11);
            for (std::size_t i = 0; i < HEIGHT; i++) {
                _matrix[i] = Vector<WIDTH>();
                for (std::size_t j = 0; j < WIDTH; j++) {
                    if (i == 0 && j == 0) {
                        _matrix[i][j] = a11;
                    } else {
                        _matrix[i][j] = va_arg(args, double);
                    }
                }
            }
            va_end(args);
        }
        Matrix(const Matrix &other) {
            for (std::size_t i = 0; i < HEIGHT; i++) {
                _matrix[i] = other._matrix[i];
            }
        }
        explicit Matrix(const Vector<HEIGHT> &vector) {
            for (std::size_t i = 0; i < HEIGHT; i++) {
                _matrix[i] = Vector<WIDTH>(vector[i]);
            }
        }
        ~Matrix() = default;

        static Matrix Identity() {
            Matrix matrix;
            for (std::size_t i = 0; i < HEIGHT; i++) {
                for (std::size_t j = 0; j < WIDTH; j++) {
                    matrix[i][j] = i == j ? 1 : 0;
                }
            }
            return matrix;
        }

        [[nodiscard]] Matrix<HEIGHT - 1, WIDTH - 1> GetMinor(const std::size_t row, const std::size_t column) const {
            if (HEIGHT != WIDTH) {
                throw std::runtime_error("Matrix must be square to have a minor");
            }
            Matrix<HEIGHT - 1, WIDTH - 1> minor;
            for (std::size_t i = 0; i < HEIGHT; i++) {
                for (std::size_t j = 0; j < WIDTH; j++) {
                    if (i != row && j != column) {
                        minor[i < row ? i : i - 1][j < column ? j : j - 1] = _matrix[i][j];
                    }
                }
            }
            return minor;
        }

        [[nodiscard]] Matrix GetAdjugate() const {
            if (HEIGHT != WIDTH) {
                throw std::runtime_error("Matrix must be square to have an adjugate");
            }
            Matrix adjugate;
            for (std::size_t i = 0; i < HEIGHT; i++) {
                for (std::size_t j = 0; j < WIDTH; j++) {
                    adjugate[i][j] = std::pow(-1, i + j) * GetMinor(i, j).GetDeterminant();
                }
            }
            return adjugate;
        }

        [[nodiscard]] int GetDeterminant() const {
            if (HEIGHT != WIDTH) {
                return 0;
            }
            if (HEIGHT == 1) {
                return _matrix[0][0];
            }
            if (HEIGHT == 2) {
                return (_matrix[0][0] * _matrix[1][1]) - (_matrix[0][1] * _matrix[1][0]);
            }
            if (HEIGHT == 3) {
                return _matrix[0][0] * _matrix[1][1] * _matrix[2][2] +
                       _matrix[0][1] * _matrix[1][2] * _matrix[2][0] +
                       _matrix[0][2] * _matrix[1][0] * _matrix[2][1] -
                       _matrix[0][2] * _matrix[1][1] * _matrix[2][0] -
                       _matrix[0][1] * _matrix[1][0] * _matrix[2][2] -
                       _matrix[0][0] * _matrix[1][2] * _matrix[2][1];
            }
            if (HEIGHT == 4) {
                const Matrix<3, 3> subMatrix1(
                    _matrix[1][1], _matrix[1][2], _matrix[1][3],
                    _matrix[2][1], _matrix[2][2], _matrix[2][3],
                    _matrix[3][1], _matrix[3][2], _matrix[3][3]);
                const Matrix<3, 3> subMatrix2(
                    _matrix[0][1], _matrix[0][2], _matrix[0][3],
                    _matrix[2][1], _matrix[2][2], _matrix[2][3],
                    _matrix[3][1], _matrix[3][2], _matrix[3][3]);
                const Matrix<3, 3> subMatrix3(
                    _matrix[0][1], _matrix[0][2], _matrix[0][3],
                    _matrix[1][1], _matrix[1][2], _matrix[1][3],
                    _matrix[3][1], _matrix[3][2], _matrix[3][3]);
                const Matrix<3, 3> subMatrix4(
                    _matrix[0][1], _matrix[0][2], _matrix[0][3],
                    _matrix[1][1], _matrix[1][2], _matrix[1][3],
                    _matrix[2][1], _matrix[2][2], _matrix[2][3]);
                return _matrix[0][0] * subMatrix1.GetDeterminant() -
                       _matrix[1][0] * subMatrix2.GetDeterminant() +
                       _matrix[2][0] * subMatrix3.GetDeterminant() -
                       _matrix[3][0] * subMatrix4.GetDeterminant();
            }
            throw std::runtime_error("Matrix determinant not implemented for N > 4");
        }

        [[nodiscard]] Vector<WIDTH> GetRow(std::size_t row) const {
            if (row >= HEIGHT) {
                throw std::out_of_range("Row index out of range");
            }
            return _matrix[row];
        }
        [[nodiscard]] Vector<HEIGHT> GetColumn(std::size_t column) const {
            if (column >= WIDTH) {
                throw std::out_of_range("Column index out of range");
            }
            Vector<HEIGHT> columnVector;
            for (std::size_t i = 0; i < HEIGHT; i++) {
                columnVector[i] = _matrix[i][column];
            }
            return columnVector;
        }
        [[nodiscard]] Matrix GetInverse() const {
            if (HEIGHT != WIDTH) {
                throw std::runtime_error("Matrix must be square to have an inverse");
            }
            double determinant = GetDeterminant();
            if (determinant == 0) {
                throw std::runtime_error("Matrix determinant is zero");
            }
            if (HEIGHT == 1) {
                return Matrix(
                    1.0 / determinant
                );
            }
            if (HEIGHT == 2) {
                return Matrix(
                    _matrix[1][1] / determinant, -_matrix[0][1] / determinant,
                    -_matrix[1][0] / determinant, _matrix[0][0] / determinant
                );
            }
            if (HEIGHT == 3) {
                Vector<WIDTH> row1 = Vector<WIDTH>(
                    _matrix[1][1] * _matrix[2][2] - _matrix[1][2] * _matrix[2][1],
                    _matrix[0][2] * _matrix[2][1] - _matrix[0][1] * _matrix[2][2],
                    _matrix[0][1] * _matrix[1][2] - _matrix[0][2] * _matrix[1][1]
                );
                Vector<WIDTH> row2 = Vector<WIDTH>(
                    _matrix[1][2] * _matrix[2][0] - _matrix[1][0] * _matrix[2][2],
                    _matrix[0][0] * _matrix[2][2] - _matrix[0][2] * _matrix[2][0],
                    _matrix[0][2] * _matrix[1][0] - _matrix[0][0] * _matrix[1][2]
                );
                Vector<WIDTH> row3 = Vector<WIDTH>(
                    _matrix[1][0] * _matrix[2][1] - _matrix[1][1] * _matrix[2][0],
                    _matrix[0][1] * _matrix[2][0] - _matrix[0][0] * _matrix[2][1],
                    _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0]
                );
                row1 /= determinant;
                row2 /= determinant;
                row3 /= determinant;

                return Matrix(
                    row1[0], row1[1], row1[2],
                    row2[0], row2[1], row2[2],
                    row3[0], row3[1], row3[2]
                );
            }
            if (HEIGHT == 4) {
                return (1.0/determinant) * this->GetAdjugate();
            }

            throw std::runtime_error("Matrix inverse not implemented for N > 4");
        }

        void SetRow(std::size_t row, Vector<WIDTH> vector) {
            if (row >= HEIGHT) {
                throw std::out_of_range("Row index out of range");
            }
            _matrix[row] = vector;
        }
        void SetColumn(std::size_t column, Vector<HEIGHT> vector) {
            if (column >= WIDTH) {
                throw std::out_of_range("Column index out of range");
            }
            for (std::size_t i = 0; i < HEIGHT; i++) {
                _matrix[i][column] = vector[i];
            }
        }

        Vector<WIDTH> operator[](std::size_t index) const {
            if (index >= HEIGHT) {
                throw std::out_of_range("Row index out of range");
            }
            return _matrix[index];
        }
        Vector<WIDTH> &operator[](std::size_t index) {
            if (index >= HEIGHT) {
                throw std::out_of_range("Row index out of range");
            }
            return _matrix[index];
        }

        Matrix operator+(const Matrix &other) const {
            Matrix result;
            for (std::size_t i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] + other[i];
            }
            return result;
        }
        Matrix operator-(const Matrix &other) const {
            Matrix result = *this + (other * -1);
            return result;
        }
        template <std::size_t OTHER_WIDTH>
        Matrix<HEIGHT, OTHER_WIDTH> operator*(const Matrix<WIDTH, OTHER_WIDTH> &other) const {
            Matrix<HEIGHT, OTHER_WIDTH> result;
            for (std::size_t i = 0; i < HEIGHT; i++) {
                for (std::size_t j = 0; j < OTHER_WIDTH; j++) {
                    result[i][j] = 0;
                    for (int k = 0; k < WIDTH; k++) {
                        result[i][j] += _matrix[i][k] * other[k][j];
                    }
                }
            }
            return result;
        }
        Matrix operator/(const Matrix &other) const {
            return *this * other.GetInverse();
        }

        Matrix operator+(const Vector<WIDTH> &other) const {
            Matrix result;
            for (std::size_t i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] + other;
            }
            return result;
        }
        Matrix operator-(const Vector<WIDTH> &other) const {
            Matrix result;
            for (std::size_t i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] - other;
            }
            return result;
        }

        Vector<HEIGHT> operator*(const Vector<WIDTH> &other) const {
            Vector<HEIGHT> result;
            Matrix<HEIGHT, 1> otherMatrix = Matrix<HEIGHT, 1>(other);
            Matrix<HEIGHT, 1> resultMatrix = (*this) * (otherMatrix);
            for (std::size_t i = 0; i < HEIGHT; i++) {
                result[i] = resultMatrix[i][0];
            }
            return result;
        }

        Matrix operator+(double scalar) const {
            Matrix result;
            for (std::size_t i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] + scalar;
            }
            return result;
        }
        Matrix operator-(double scalar) const {
            Matrix result;
            for (std::size_t i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] - scalar;
            }
            return result;
        }
        Matrix operator*(double scalar) const {
            Matrix result;
            for (std::size_t i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] * scalar;
            }
            return result;
        }
        Matrix operator/(double scalar) const {
            Matrix result;
            for (int i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] / scalar;
            }
            return result;
        }

        friend Matrix operator+(double scalar, const Matrix &matrix) {
            return matrix + scalar;
        }
        friend Matrix operator-(double scalar, const Matrix &matrix) {
            return matrix - scalar;
        }
        friend Matrix operator*(double scalar, const Matrix &matrix) {
            return matrix * scalar;
        }
        friend Matrix operator/(double scalar, const Matrix &matrix) {
            return matrix / scalar;
        }

        Matrix &operator+=(const Matrix &other) {
            *this = *this + other;
            return *this;
        }
        Matrix &operator-=(const Matrix &other) {
            *this = *this - other;
            return *this;
        }
        Matrix &operator*=(const Matrix &other) {
            *this = *this * other;
            return *this;
        }
        Matrix &operator/=(const Matrix &other) {
            *this = *this / other;
            return *this;
        }

        Matrix &operator+=(const Vector<WIDTH> &other) {
            *this = *this + other;
            return *this;
        }
        Matrix &operator-=(const Vector<WIDTH> &other) {
            *this = *this - other;
            return *this;
        }
        Matrix &operator*=(const Vector<WIDTH> &other) {
            *this = *this * other;
            return *this;
        }
        Matrix &operator/=(const Vector<WIDTH> &other) {
            *this = *this / other;
            return *this;
        }

        Matrix &operator+=(double scalar) {
            *this = *this + scalar;
            return *this;
        }
        Matrix &operator-=(double scalar) {
            *this = *this - scalar;
            return *this;
        }
        Matrix &operator*=(double scalar) {
            *this = *this * scalar;
            return *this;
        }
        Matrix &operator/=(double scalar) {
            *this = *this / scalar;
            return *this;
        }

        bool operator==(const Matrix &other) const {
            for (int i = 0; i < HEIGHT; i++) {
                if (_matrix[i] != other[i]) {
                    return false;
                }
            }
            return true;
        }
        bool operator!=(const Matrix &other) const {
            return !(*this == other);
        }
    };

    class MatrixFactory {
    public:
        static Matrix<4, 4> TranslationMatrix(const double x, const double y, const double z) {
            return Matrix<4, 4>(
                1.0, 0.0, 0.0, x,
                0.0, 1.0, 0.0, y,
                0.0, 0.0, 1.0, z,
                0.0, 0.0, 0.0, 1.0
            );
        }
        static Matrix<4, 4> ScaleMatrix(const double x, const double y, const double z) {
            return Matrix<4, 4>(
                x, 0.0, 0.0, 0.0,
                0.0, y, 0.0, 0.0,
                0.0, 0.0, z, 0.0,
                0.0, 0.0, 0.0, 1.0
            );
        }
    };
}
