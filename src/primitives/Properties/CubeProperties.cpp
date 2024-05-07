/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Properties/CubeProperties.hpp"

CubeProperties::CubeProperties() : AbstractProperties()
{
    _size = 1.0f;
}

CubeProperties::CubeProperties(float size) : AbstractProperties()
{
    _size = size;
}

CubeProperties::CubeProperties(JsonObject *obj) : AbstractProperties(obj)
{
    _size = obj->getFloat("size");
}

float CubeProperties::getSize() const
{
    return _size;
}

float &CubeProperties::getSize()
{
    return _size;
}

void CubeProperties::setSize(float size)
{
    _size = size;
}
