/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform {
protected:
    glm::vec3 _position{};
    glm::dquat _rotation{};
    glm::vec3 _scale{};
public:
    Transform();
    Transform(const glm::vec3 &position, const glm::dquat &rotation, const glm::vec3 &scale);
    Transform(const Transform &other);
    ~Transform() = default;

    [[nodiscard]] glm::vec3 getPosition() const;
    [[nodiscard]] glm::dquat getRotation() const;
    [[nodiscard]] glm::vec3 getScale() const;

    [[nodiscard]] glm::vec3 &getPosition();
    [[nodiscard]] glm::dquat &getRotation();
    [[nodiscard]] glm::vec3 &getScale();

    void setPosition(const glm::vec3 &position);
    void setRotation(const glm::dquat &rotation);
    void setScale(const glm::vec3 &scale);

    void translate(const glm::vec3 &translation);
    void rotate(const glm::dquat &rotation);
    void scale(const glm::vec3 &scale);
    void translate(const float x, const float y, const float z);
    void rotate(const float x, const float y, const float z);
    void scale(const float x, const float y, const float z);

    [[nodiscard]] glm::mat4 getTranslationMatrix() const;
    [[nodiscard]] glm::mat4 getRotationMatrix() const;
    [[nodiscard]] glm::mat4 getScaleMatrix() const;
    [[nodiscard]] glm::mat4 getTransformationMatrix() const;
};
