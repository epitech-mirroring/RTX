/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "GLSL/Vector.hpp"
#include "GLSL/Matrix.hpp"

class Transform {
protected:
    GLSL::Vector<3> _position;
    GLSL::Vector<3> _rotation;
    GLSL::Vector<3> _scale;
public:
    Transform();
    Transform(GLSL::Vector<3> position, GLSL::Vector<3> rotation, GLSL::Vector<3> scale);
    Transform(const Transform &other);
    ~Transform();

    GLSL::Vector<3> GetPosition() const;
    GLSL::Vector<3> GetRotation() const;
    GLSL::Vector<3> GetScale() const;

    void SetPosition(GLSL::Vector<3> position);
    void SetRotation(GLSL::Vector<3> rotation);
    void SetScale(GLSL::Vector<3> scale);

    void Translate(GLSL::Vector<3> translation);
    void Rotate(GLSL::Vector<3> rotation);
    void Scale(GLSL::Vector<3> scale);
    void Translate(float x, float y, float z);
    void Rotate(float x, float y, float z);
    void Scale(float x, float y, float z);

    GLSL::Matrix<4, 4> ToWorldMatrix() const;
};
