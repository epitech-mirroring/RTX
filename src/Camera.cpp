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

Camera::Camera(const Transform &transform, const float fov, const float aspect,
               const float near)
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

float Camera::getFov() const
{
    return this->_fov;
}

float &Camera::getFov()
{
    return this->_fov;
}

float Camera::getAspect() const
{
    return this->_aspect;
}

float &Camera::getAspect()
{
    return this->_aspect;
}

float Camera::getNear() const
{
    return this->_near;
}

float &Camera::getNear()
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

void Camera::setFov(const float fov)
{
    this->_fov = fov;
}

void Camera::setAspect(const float aspect)
{
    this->_aspect = aspect;
}

void Camera::setNear(const float near)
{
    this->_near = near;
}

void Camera::setTransform(const Transform& transform)
{
    this->_transform = transform;
}
