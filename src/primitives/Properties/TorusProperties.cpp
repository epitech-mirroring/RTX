/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Properties/TorusProperties.hpp"

TorusProperties::TorusProperties() : AbstractProperties()
{
    _radius = 0;
    _middleRadius = 0;
}

TorusProperties::TorusProperties(float radius, float middleRadius) : AbstractProperties()
{
    _radius = radius;
    _middleRadius = middleRadius;
}

TorusProperties::TorusProperties(JsonObject *obj) : AbstractProperties(obj)
{
    _radius = obj->getFloat("radius");
    _middleRadius = obj->getFloat("middleRadius");
}

void TorusProperties::SetRadius(float radius)
{
    _radius = radius;
}

void TorusProperties::SetMiddleRadius(float middleRadius)
{
    _middleRadius = middleRadius;
}

float TorusProperties::GetRadius() const
{
    return _radius;
}

float TorusProperties::GetMiddleRadius() const
{
    return _middleRadius;
}

float &TorusProperties::GetRadius()
{
    return _radius;
}

float &TorusProperties::GetMiddleRadius()
{
    return _middleRadius;
}
