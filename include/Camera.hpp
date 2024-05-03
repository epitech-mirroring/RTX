/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Transform.hpp"
#include "json/Json.hpp"

class Camera {
protected:
    Transform _transform;
    double _fov;
    double _aspect;
    double _near;
public:
    Camera();
    Camera(const Transform &transform, double fov, double aspect, double near);
    Camera(const Camera &other);
    explicit Camera(JsonObject *obj);
    ~Camera() = default;

    [[nodiscard]] double getFov() const;
    [[nodiscard]] double getAspect() const;
    [[nodiscard]] double getNear() const;
    [[nodiscard]] Transform getTransform() const;

    [[nodiscard]] double &getFov();
    [[nodiscard]] double &getAspect();
    [[nodiscard]] double &getNear();
    [[nodiscard]] Transform &getTransform();

    void setFov(double fov);
    void setAspect(double aspect);
    void setNear(double near);
    void setTransform(const Transform& transform);
};
