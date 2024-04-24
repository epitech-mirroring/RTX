/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Transform.hpp"

class Camera {
protected:
    Transform _transform;
    float _fov;
    float _aspect;
    float _near;
public:
    Camera();
    Camera(Transform transform, float fov, float aspect, float near);
    Camera(const Camera &other);
    ~Camera();

    float GetFov() const;
    float GetAspect() const;
    float GetNear() const;
    Transform GetTransform() const;

    void SetFov(float fov);
    void SetAspect(float aspect);
    void SetNear(float near);
};
