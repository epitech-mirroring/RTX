/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "GLSL/Vector.hpp"
#include <exception>
#include <stdexcept>
#include <cmath>
#include <cstdarg>
#include <cstdio>

namespace GLSL {
    template <int HEIGHT, int WIDTH>
    class Matrix {
    private:
        Vector<WIDTH> _matrix[HEIGHT];
    public:
        Matrix() {
            for (int i = 0; i < HEIGHT; i++) {
                _matrix[i] = Vector<WIDTH>();
            }
        }
        explicit Matrix(double a11, ...) {
            va_list args;
            va_start(args, a11);
            for (int i = 0; i < HEIGHT; i++) {
                _matrix[i] = Vector<WIDTH>();
                for (int j = 0; j < WIDTH; j++) {
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
            for (int i = 0; i < HEIGHT; i++) {
                _matrix[i] = other._matrix[i];
            }
        }
        ~Matrix() = default;

        static Matrix<HEIGHT, WIDTH> Identity() {
            Matrix<HEIGHT, WIDTH> matrix;
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    matrix[i][j] = i == j ? 1 : 0;
                }
            }
            return matrix;
        }

        [[nodiscard]] Matrix<HEIGHT - 1, WIDTH - 1> GetMinor(int row, int column) const {
            if (HEIGHT != WIDTH) {
                throw std::runtime_error("Matrix must be square to have a minor");
            }
            Matrix<HEIGHT - 1, WIDTH - 1> minor;
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    if (i != row && j != column) {
                        minor[i < row ? i : i - 1][j < column ? j : j - 1] = _matrix[i][j];
                    }
                }
            }
            return minor;
        }

        [[nodiscard]] Matrix<HEIGHT, WIDTH> GetAdjugate() const {
            if (HEIGHT != WIDTH) {
                throw std::runtime_error("Matrix must be square to have an adjugate");
            }
            Matrix<HEIGHT, WIDTH> adjugate;
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
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
                Matrix<3, 3> subMatrix1(
                    _matrix[1][1], _matrix[1][2], _matrix[1][3],
                    _matrix[2][1], _matrix[2][2], _matrix[2][3],
                    _matrix[3][1], _matrix[3][2], _matrix[3][3]);
                Matrix<3, 3> subMatrix2(
                    _matrix[0][1], _matrix[0][2], _matrix[0][3],
                    _matrix[2][1], _matrix[2][2], _matrix[2][3],
                    _matrix[3][1], _matrix[3][2], _matrix[3][3]);
                Matrix<3, 3> subMatrix3(
                    _matrix[0][1], _matrix[0][2], _matrix[0][3],
                    _matrix[1][1], _matrix[1][2], _matrix[1][3],
                    _matrix[3][1], _matrix[3][2], _matrix[3][3]);
                Matrix<3, 3> subMatrix4(
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
        [[nodiscard]] Matrix<HEIGHT, WIDTH> GetInverse() const {
            if (HEIGHT != WIDTH) {
                throw std::runtime_error("Matrix must be square to have an inverse");
            }
            float determinant = GetDeterminant();
            if (determinant == 0) {
                throw std::runtime_error("Matrix determinant is zero");
            }
            if (HEIGHT == 1) {
                return Matrix<HEIGHT, WIDTH>(
                    1 / determinant
                );
            }
            if (HEIGHT == 2) {
                return Matrix<HEIGHT, WIDTH>(
                    _matrix[1][1] / determinant, -_matrix[0][1] / determinant,
                    -_matrix[1][0] / determinant, _matrix[0][0] / determinant
                );
            }
            if (HEIGHT == 3) {
                Vector<WIDTH> row1 = Vector<WIDTH>({
                    _matrix[1][1] * _matrix[2][2] - _matrix[1][2] * _matrix[2][1],
                    _matrix[0][2] * _matrix[2][1] - _matrix[0][1] * _matrix[2][2],
                    _matrix[0][1] * _matrix[1][2] - _matrix[0][2] * _matrix[1][1]
                });
                Vector<WIDTH> row2 = Vector<WIDTH>({
                    _matrix[1][2] * _matrix[2][0] - _matrix[1][0] * _matrix[2][2],
                    _matrix[0][0] * _matrix[2][2] - _matrix[0][2] * _matrix[2][0],
                    _matrix[0][2] * _matrix[1][0] - _matrix[0][0] * _matrix[1][2]
                });
                Vector<WIDTH> row3 = Vector<WIDTH>({
                    _matrix[1][0] * _matrix[2][1] - _matrix[1][1] * _matrix[2][0],
                    _matrix[0][1] * _matrix[2][0] - _matrix[0][0] * _matrix[2][1],
                    _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0]
                });
                row1 /= determinant;
                row2 /= determinant;
                row3 /= determinant;

                return Matrix<HEIGHT, WIDTH>(
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

        Vector<WIDTH> operator[](int index) const {
            if (index >= HEIGHT) {
                throw std::out_of_range("Row index out of range");
            }
            return _matrix[index];
        }
        Vector<WIDTH> &operator[](int index) {
            if (index >= HEIGHT) {
                throw std::out_of_range("Row index out of range");
            }
            return _matrix[index];
        }

        Matrix<HEIGHT, WIDTH> operator+(const Matrix<HEIGHT, WIDTH> &other) const {
            Matrix<HEIGHT, WIDTH> result;
            for (int i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] + other[i];
            }
            return result;
        }
        Matrix<HEIGHT, WIDTH> operator-(const Matrix<HEIGHT, WIDTH> &other) const {
            Matrix<HEIGHT, WIDTH> result = *this + (other * -1);
            return result;
        }
        template <int OTHER_WIDTH>
        Matrix<HEIGHT, OTHER_WIDTH> operator*(const Matrix<WIDTH, OTHER_WIDTH> &other) const {
            Matrix<HEIGHT, OTHER_WIDTH> result;
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < OTHER_WIDTH; j++) {
                    result[i][j] = 0;
                    for (int k = 0; k < WIDTH; k++) {
                        result[i][j] += _matrix[i][k] * other[k][j];
                    }
                }
            }
            return result;
        }
        Matrix<HEIGHT, WIDTH> operator/(const Matrix<HEIGHT, WIDTH> &other) const {
            return *this * other.GetInverse();
        }

        Matrix<HEIGHT, WIDTH> operator+(const Vector<WIDTH> &other) const {
            Matrix<HEIGHT, WIDTH> result;
            for (int i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] + other;
            }
            return result;
        }
        Matrix<HEIGHT, WIDTH> operator-(const Vector<WIDTH> &other) const {
            Matrix<HEIGHT, WIDTH> result;
            for (int i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] - other;
            }
            return result;
        }
        Matrix<HEIGHT, WIDTH> operator*(const Vector<WIDTH> &other) const {
            Matrix<HEIGHT, WIDTH> result;
            for (int i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] * other;
            }
            return result;
        }
        Matrix<HEIGHT, WIDTH> operator/(const Vector<WIDTH> &other) const {
            Matrix<HEIGHT, WIDTH> result;
            for (int i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] / other;
            }
            return result;
        }

        Matrix<HEIGHT, WIDTH> operator+(float scalar) const {
            Matrix<HEIGHT, WIDTH> result;
            for (int i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] + scalar;
            }
            return result;
        }
        Matrix<HEIGHT, WIDTH> operator-(float scalar) const {
            Matrix<HEIGHT, WIDTH> result;
            for (int i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] - scalar;
            }
            return result;
        }
        Matrix<HEIGHT, WIDTH> operator*(float scalar) const {
            Matrix<HEIGHT, WIDTH> result;
            for (int i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] * scalar;
            }
            return result;
        }
        Matrix<HEIGHT, WIDTH> operator/(float scalar) const {
            Matrix<HEIGHT, WIDTH> result;
            for (int i = 0; i < HEIGHT; i++) {
                result[i] = _matrix[i] / scalar;
            }
            return result;
        }

        friend Matrix<HEIGHT, WIDTH> operator+(float scalar, const Matrix<HEIGHT, WIDTH> &matrix) {
            return matrix + scalar;
        }
        friend Matrix<HEIGHT, WIDTH> operator-(float scalar, const Matrix<HEIGHT, WIDTH> &matrix) {
            return matrix - scalar;
        }
        friend Matrix<HEIGHT, WIDTH> operator*(float scalar, const Matrix<HEIGHT, WIDTH> &matrix) {
            return matrix * scalar;
        }
        friend Matrix<HEIGHT, WIDTH> operator/(float scalar, const Matrix<HEIGHT, WIDTH> &matrix) {
            return matrix / scalar;
        }

        Matrix<HEIGHT, WIDTH> &operator+=(const Matrix<HEIGHT, WIDTH> &other) {
            *this = *this + other;
            return *this;
        }
        Matrix<HEIGHT, WIDTH> &operator-=(const Matrix<HEIGHT, WIDTH> &other) {
            *this = *this - other;
            return *this;
        }
        Matrix<HEIGHT, WIDTH> &operator*=(const Matrix<HEIGHT, WIDTH> &other) {
            *this = *this * other;
            return *this;
        }
        Matrix<HEIGHT, WIDTH> &operator/=(const Matrix<HEIGHT, WIDTH> &other) {
            *this = *this / other;
            return *this;
        }

        Matrix<HEIGHT, WIDTH> &operator+=(const Vector<WIDTH> &other) {
            *this = *this + other;
            return *this;
        }
        Matrix<HEIGHT, WIDTH> &operator-=(const Vector<WIDTH> &other) {
            *this = *this - other;
            return *this;
        }
        Matrix<HEIGHT, WIDTH> &operator*=(const Vector<WIDTH> &other) {
            *this = *this * other;
            return *this;
        }
        Matrix<HEIGHT, WIDTH> &operator/=(const Vector<WIDTH> &other) {
            *this = *this / other;
            return *this;
        }

        Matrix<HEIGHT, WIDTH> &operator+=(float scalar) {
            *this = *this + scalar;
            return *this;
        }
        Matrix<HEIGHT, WIDTH> &operator-=(float scalar) {
            *this = *this - scalar;
            return *this;
        }
        Matrix<HEIGHT, WIDTH> &operator*=(float scalar) {
            *this = *this * scalar;
            return *this;
        }
        Matrix<HEIGHT, WIDTH> &operator/=(float scalar) {
            *this = *this / scalar;
            return *this;
        }

        bool operator==(const Matrix<HEIGHT, WIDTH> &other) const {
            for (int i = 0; i < HEIGHT; i++) {
                if (_matrix[i] != other[i]) {
                    return false;
                }
            }
            return true;
        }
        bool operator!=(const Matrix<HEIGHT, WIDTH> &other) const {
            return *this != other;
        }
    };

    class MatrixFactory {
    public:
        static Matrix<4, 4> TranslationMatrix(float x, float y, float z) {
            return Matrix<4, 4>(
                1, 0, 0, x,
                0, 1, 0, y,
                0, 0, 1, z,
                0, 0, 0, 1
            );
        }
        static Matrix<4, 4> RotationMatrix(float x, float y, float z) {
            Matrix<4, 4> xRotation = Matrix<4, 4>::Identity();
            xRotation[1][1] = cos(x);
            xRotation[1][2] = -sin(x);
            xRotation[2][1] = sin(x);
            xRotation[2][2] = cos(x);
            Matrix<4, 4> yRotation = Matrix<4, 4>::Identity();
            yRotation[0][0] = cos(y);
            yRotation[0][2] = sin(y);
            yRotation[2][0] = -sin(y);
            yRotation[2][2] = cos(y);
            Matrix<4, 4> zRotation = Matrix<4, 4>::Identity();
            zRotation[0][0] = cos(z);
            zRotation[0][1] = -sin(z);
            zRotation[1][0] = sin(z);
            zRotation[1][1] = cos(z);
            return xRotation * yRotation * zRotation;
        }
        static Matrix<4, 4> ScaleMatrix(float x, float y, float z) {
            return Matrix<4, 4>(
                x, 0, 0, 0,
                0, y, 0, 0,
                0, 0, z, 0,
                0, 0, 0, 1
            );
        }
    };
}
