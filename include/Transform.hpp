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
#include "GLSL/Quaternion.hpp"
#include "json/Json.hpp"

class Transform {
protected:
    GLSL::Vector<3> _position;
    GLSL::Quaternion _rotation;
    GLSL::Vector<3> _scale;
public:
    Transform() {
        _position = GLSL::Vector<3>(0.0, 0.0, 0.0);
        _rotation = GLSL::Quaternion(0.0, 0.0, 0.0, 1.0);
        _scale = GLSL::Vector<3>(1.0, 1.0, 1.0);
    }
    Transform(const GLSL::Vector<3>& position, const GLSL::Quaternion &rotation, const GLSL::Vector<3>& scale) {
        _position = position;
        _rotation = rotation;
        _scale = scale;
    }
    Transform(const Transform &other) {
        _position = other.getPosition();
        _rotation = other.getRotation();
        _scale = other.getScale();
    }
    explicit Transform(JsonObject *obj) {
        _position = GLSL::Vector<3>(obj->getValue<JsonArray>("position"));
        _rotation = GLSL::Quaternion(obj->getValue<JsonObject>("rotation"));
        _scale = GLSL::Vector<3>(obj->getValue<JsonArray>("scale"));
    }
    ~Transform() = default;

    [[nodiscard]] GLSL::Vector<3> getPosition() const { return _position; }
    [[nodiscard]] GLSL::Quaternion getRotation() const { return _rotation; }
    [[nodiscard]] GLSL::Vector<3> getScale() const { return _scale; }

    [[nodiscard]] GLSL::Vector<3> &getPosition() { return _position; }
    [[nodiscard]] GLSL::Quaternion &getRotation() { return _rotation; }
    [[nodiscard]] GLSL::Vector<3> &getScale() { return _scale; }

    void setPosition(const GLSL::Vector<3> &position) { _position = position; }
    void setRotation(const GLSL::Quaternion &rotation) { _rotation = rotation; }
    void setScale(const GLSL::Vector<3> &scale) { _scale = scale; }

    void translate(const GLSL::Vector<3> &translation) { _position += translation; }
    void rotate(const GLSL::Quaternion &rotation) {
        _rotation *= rotation;
    }
    void scale(const GLSL::Vector<3> &scale) { _scale.x() *= scale.x(); _scale.y() *= scale.y(); _scale.z() *= scale.z(); }
    void translate(const float x, const float y, const float z) { _position += GLSL::Vector<3>(x, y, z); }
    void rotate(const float x, const float y, const float z) {
        _rotation *= GLSL::Quaternion(x, y, z);
    }
    void scale(const float x, const float y, const float z) { _scale.x() *= x; _scale.y() *= y; _scale.z() *= z; }

    [[nodiscard]] GLSL::Matrix<4, 4> getTransformationMatrix() const {
        GLSL::Matrix<4, 4> translationMatrix = GLSL::Matrix<4, 4>::Identity();
        translationMatrix[0][3] = _position.x();
        translationMatrix[1][3] = _position.y();
        translationMatrix[2][3] = _position.z();
        const double &q0 = _rotation.w;
        const double &q1 = _rotation.x;
        const double &q2 = _rotation.y;
        const double &q3 = _rotation.z;

        GLSL::Matrix<4, 4> rotationMatrix = GLSL::Matrix<4, 4>::Identity();
        rotationMatrix[0][0] = 2 * (q0 * q0 + q1 * q1) - 1;
        rotationMatrix[0][1] = 2 * (q1 * q2 - q0 * q3);
        rotationMatrix[0][2] = 2 * (q1 * q3 + q0 * q2);
        rotationMatrix[1][0] = 2 * (q1 * q2 + q0 * q3);
        rotationMatrix[1][1] = 2 * (q0 * q0 + q2 * q2) - 1;
        rotationMatrix[1][2] = 2 * (q2 * q3 - q0 * q1);
        rotationMatrix[2][0] = 2 * (q1 * q3 - q0 * q2);
        rotationMatrix[2][1] = 2 * (q2 * q3 + q0 * q1);
        rotationMatrix[2][2] = 2 * (q0 * q0 + q3 * q3) - 1;

        GLSL::Matrix<4, 4> scaleMatrix = GLSL::Matrix<4, 4>::Identity();
        scaleMatrix[0][0] = _scale.x();
        scaleMatrix[1][1] = _scale.y();
        scaleMatrix[2][2] = _scale.z();

        return translationMatrix * rotationMatrix * scaleMatrix;
    }
};
