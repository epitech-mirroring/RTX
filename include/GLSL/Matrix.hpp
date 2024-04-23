/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "GLSL/Vector.hpp"

namespace GLSL {
    template <int N, int M>
    class Matrix {
    private:
        Vector<M> _matrix[N];
    public:
        Matrix();
        Matrix(Vector<M> matrix[N]);
        Matrix(const Matrix &other);
        ~Matrix();

        int GetDeterminant() const;

        Vector<M> GetRow(int row) const;
        Vector<N> GetColumn(int column) const;

        void SetRow(int row, Vector<M> vector);
        void SetColumn(int column, Vector<N> vector);

        Vector<M> operator[](int index) const;
        Vector<M> &operator[](int index);

        Matrix<N, M> operator+(const Matrix<N, M> &other) const;
        Matrix<N, M> operator-(const Matrix<N, M> &other) const;
        Matrix<N, M> operator*(const Matrix<N, M> &other) const;
        Matrix<N, M> operator/(const Matrix<N, M> &other) const;

        Matrix<N, M> operator+(const Vector<M> &other) const;
        Matrix<N, M> operator-(const Vector<M> &other) const;
        Matrix<N, M> operator*(const Vector<M> &other) const;
        Matrix<N, M> operator/(const Vector<M> &other) const;

        Matrix<N, M> operator+(float scalar) const;
        Matrix<N, M> operator-(float scalar) const;
        Matrix<N, M> operator*(float scalar) const;
        Matrix<N, M> operator/(float scalar) const;

        Matrix<N, M> &operator+=(const Matrix<N, M> &other);
        Matrix<N, M> &operator-=(const Matrix<N, M> &other);
        Matrix<N, M> &operator*=(const Matrix<N, M> &other);
        Matrix<N, M> &operator/=(const Matrix<N, M> &other);

        Matrix<N, M> &operator+=(const Vector<M> &other);
        Matrix<N, M> &operator-=(const Vector<M> &other);
        Matrix<N, M> &operator*=(const Vector<M> &other);
        Matrix<N, M> &operator/=(const Vector<M> &other);

        Matrix<N, M> &operator+=(float scalar);
        Matrix<N, M> &operator-=(float scalar);
        Matrix<N, M> &operator*=(float scalar);
        Matrix<N, M> &operator/=(float scalar);

        bool operator==(const Matrix<N, M> &other) const;
        bool operator!=(const Matrix<N, M> &other) const;
    };
}
