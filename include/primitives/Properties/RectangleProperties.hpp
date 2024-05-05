/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <cstddef>
#include "primitives/Properties/AbstractProperties.hpp"
#include "json/Json.hpp"

class RectangleProperties : public AbstractProperties {
    public:
        RectangleProperties() : AbstractProperties() { _length = 1; _width = 1; _height = 1; };
        explicit RectangleProperties(float length, float width, float height) : AbstractProperties() { _length = length; _width = width; _height = height;};
        explicit RectangleProperties(JsonObject *obj) : AbstractProperties(obj) { _length = obj->getFloat("length");
            _width = obj->getFloat("width"); _height = obj->getFloat("height");};
        ~RectangleProperties() override = default;
        float getLength() const { return _length; }
        float &getLength() { return _length; }
        float getWidth() const { return _width; }
        float &getWidth() { return _width; }
        float getHeight() const { return _height; }
        float &getHeight() { return _height; }
        void setLength(float length) { _length = length; }
        void setWidth(float width) { _width = width; }
        void setHeight(float height) { _height = height; }
    protected:
        float _length;
        float _width;
        float _height;
};
