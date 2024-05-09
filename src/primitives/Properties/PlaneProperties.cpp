/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Properties/PlaneProperties.hpp"
#include <iostream>

PlaneProperties::PlaneProperties() : AbstractProperties()
{
    _height = 0.0f;
    _width = 0.0f;
}

PlaneProperties::PlaneProperties(const float height, const float width) : AbstractProperties()
{
    _height = height;
    _width = width;
}

PlaneProperties::PlaneProperties(JsonObject *obj) : AbstractProperties(obj){
    _height = obj->getFloat("height");
    _width = obj->getFloat("width");
}

float PlaneProperties::getHeight() const
{
    return _height;
}

float &PlaneProperties::getHeight()
{
    return _height;
}

float PlaneProperties::getWidth() const
{
    return _width;
}

float &PlaneProperties::getWidth()
{
    return _width;
}

void PlaneProperties::setHeight(float height)
{
    _height = height;
}

void PlaneProperties::setWidth(float width)
{
    _width = width;
}