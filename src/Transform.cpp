/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Transform.hpp"

Transform::Transform()
{
    _position = glm::vec3(0.0, 0.0, 0.0);
    _rotation = glm::dquat(1.0, 0.0, 0.0, 0.0);
    _scale = glm::vec3(1.0, 1.0, 1.0);
}

Transform::Transform(const glm::vec3 &position, const glm::dquat &rotation, const glm::vec3 &scale)
{
    _position = position;
    _rotation = rotation;
    _scale = scale;
}

Transform::Transform(const Transform &other)
{
    _position = other._position;
    _rotation = other._rotation;
    _scale = other._scale;
}

Transform::Transform(JsonObject *obj)
{
    _position = GlmParser::parseVec3(obj->getValue<JsonObject>("position"));
    _rotation = glm::dquat(1.0, 0.0, 0.0, 0.0);
    glm::vec3 rotation = GlmParser::parseVec3(obj->getValue<JsonObject>("rotation"));
    this->rotate(glm::vec3(1.0, 0.0, 0.0), glm::radians((float)rotation.x));
    this->rotate(glm::vec3(0.0, 1.0, 0.0), glm::radians((float)rotation.y));
    this->rotate(glm::vec3(0.0, 0.0, 1.0), glm::radians((float)rotation.z));
    _scale = GlmParser::parseVec3(obj->getValue<JsonObject>("scale"));
}

glm::vec3 Transform::getPosition() const
{
    return _position;
}

glm::dquat Transform::getRotation() const
{
    return _rotation;
}

glm::vec3 Transform::getScale() const
{
    return _scale;
}

glm::vec3 &Transform::getPosition()
{
    return _position;
}

glm::dquat &Transform::getRotation()
{
    return _rotation;
}

glm::vec3 &Transform::getScale()
{
    return _scale;
}

void Transform::setPosition(const glm::vec3 &position)
{
    _position = position;
}

void Transform::setRotation(const glm::dquat &rotation)
{
    _rotation = rotation;
}

void Transform::setScale(const glm::vec3 &scale)
{
    _scale = scale;
}

void Transform::translate(const glm::vec3 &translation)
{
    _position += translation;
}

void Transform::rotate(const glm::dquat &rotation)
{
    _rotation = rotation * _rotation;
}

void Transform::scale(const glm::vec3 &scale)
{
    _scale *= scale;
}

void Transform::translate(const float x, const float y, const float z)
{
    _position += glm::vec3(x, y, z);
}

void Transform::rotate(const glm::vec3 &axis, const float angle)
{
    _rotation *= glm::angleAxis(angle, axis);
}

void Transform::scale(const float x, const float y, const float z)
{
    _scale *= glm::vec3(x, y, z);
}

glm::mat4 Transform::getTranslationMatrix() const
{
    return glm::translate(glm::mat4(1.0), _position);
}

glm::mat4 Transform::getRotationMatrix() const
{
    return glm::mat4_cast(_rotation);
}

glm::mat4 Transform::getScaleMatrix() const
{
    return glm::scale(glm::mat4(1.0), _scale);
}

glm::mat4 Transform::getTransformationMatrix() const
{
    return getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
}
