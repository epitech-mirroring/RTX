/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Properties/ConeProperties.hpp"

ConeProperties::ConeProperties() : AbstractProperties()
{
    _radius = 0;
    _height = 0;
}

ConeProperties::ConeProperties(float radius, float height) : AbstractProperties()
{
    _radius = radius;
    _height = height;
}

ConeProperties::ConeProperties(JsonObject *obj) : AbstractProperties(obj)
{
    _radius = obj->getFloat("radius");
    _height = obj->getFloat("height");
}

void ConeProperties::SetRadius(float radius)
{
    _radius = radius;
}

void ConeProperties::SetHeight(float height)
{
    _height = height;
}

float ConeProperties::GetRadius() const
{
    return _radius;
}

float ConeProperties::GetHeight() const
{
    return _height;
}

float &ConeProperties::GetRadius()
{
    return _radius;
}

float &ConeProperties::GetHeight()
{
    return _height;
}
