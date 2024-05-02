/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Transform.hpp"
#include <cmath>

#define DEG_TO_RAD(x) (x * M_PI / 180)

class Camera {
protected:
    Transform _transform;
    float _fov;
    float _aspect;
    float _near;
public:
    Camera();
    Camera(const Transform &transform, float fov, float aspect, float near);
    Camera(const Camera &other);
    ~Camera() = default;

    [[nodiscard]] float getFov() const;
    [[nodiscard]] float getAspect() const;
    [[nodiscard]] float getNear() const;
    [[nodiscard]] Transform getTransform() const;

    [[nodiscard]] float &getFov();
    [[nodiscard]] float &getAspect();
    [[nodiscard]] float &getNear();
    [[nodiscard]] Transform &getTransform();

    void setFov(float fov);
    void setAspect(float aspect);
    void setNear(float near);
    void setTransform(const Transform& transform);
    [[nodiscard]] glm::vec3 getViewParams() const;
};
