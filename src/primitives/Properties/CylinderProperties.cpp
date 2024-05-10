/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Properties/CylinderProperties.hpp"

CylinderProperties::CylinderProperties() : AbstractProperties()
{
    _radius = 0;
    _height = 0;
}

CylinderProperties::CylinderProperties(float radius, float height) : AbstractProperties()
{
    _radius = radius;
    _height = height;
}

CylinderProperties::CylinderProperties(JsonObject *obj) : AbstractProperties(obj)
{
    _radius = obj->getFloat("radius");
    _height = obj->getFloat("height");
}

void CylinderProperties::SetRadius(float radius)
{
    _radius = radius;
}

void CylinderProperties::SetHeight(float height)
{
    _height = height;
}

float CylinderProperties::GetRadius() const
{
    return _radius;
}

float CylinderProperties::GetHeight() const
{
    return _height;
}

float &CylinderProperties::GetRadius()
{
    return _radius;
}

float &CylinderProperties::GetHeight()
{
    return _height;
}
