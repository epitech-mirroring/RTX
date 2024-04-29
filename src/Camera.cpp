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

Camera::Camera(Transform transform, float fov, float aspect, float near)
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

float Camera::GetFov() const
{
    return this->_fov;
}

float Camera::GetAspect() const
{
    return this->_aspect;
}

float Camera::GetNear() const
{
    return this->_near;
}

Transform Camera::GetTransform() const
{
    return this->_transform;
}

void Camera::SetFov(float fov)
{
    this->_fov = fov;
}

void Camera::SetAspect(float aspect)
{
    this->_aspect = aspect;
}

void Camera::SetNear(float near)
{
    this->_near = near;
}
