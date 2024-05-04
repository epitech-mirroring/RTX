/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** Camera.cpp
*/

#include "Camera.hpp"

Camera::Camera()
{
    this->_transform = Transform();
    this->_fov = 0;
    this->_aspect = 0;
    this->_near = 0;
}

Camera::Camera(const Transform &transform, const double fov, const double aspect,
               const double near)
{
    this->_transform = transform;
    this->_fov = fov;
    this->_aspect = aspect;
    this->_near = near;
}

Camera::Camera(const Camera &other)
{
    this->_transform = other._transform;
    this->_fov = other._fov;
    this->_aspect = other._aspect;
    this->_near = other._near;
}

Camera::Camera(JsonObject *obj)
{
    this->_transform = Transform(obj->getValue<JsonObject>("transform"));
    this->_fov = obj->getFloat("fov");
    this->_aspect = obj->getFloat("aspect");
    this->_near = obj->getFloat("near");
}

double Camera::getFov() const
{
    return this->_fov;
}

double &Camera::getFov()
{
    return this->_fov;
}

double Camera::getAspect() const
{
    return this->_aspect;
}

double &Camera::getAspect()
{
    return this->_aspect;
}

double Camera::getNear() const
{
    return this->_near;
}

double &Camera::getNear()
{
    return this->_near;
}

Transform Camera::getTransform() const
{
    return this->_transform;
}

Transform &Camera::getTransform()
{
    return this->_transform;
}

void Camera::setFov(const double fov)
{
    this->_fov = fov;
}

void Camera::setAspect(const double aspect)
{
    this->_aspect = aspect;
}

void Camera::setNear(const double near)
{
    this->_near = near;
}

void Camera::setTransform(const Transform& transform)
{
    this->_transform = transform;
}

glm::vec3 Camera::getViewParams() const
{
    double planeHeight = this->_near * tan(DEG_TO_RAD(this->_fov * 0.5f)) * 2.0f;
    double planeWidth = planeHeight * this->_aspect;
    return {planeWidth, planeHeight, this->_near};
}
