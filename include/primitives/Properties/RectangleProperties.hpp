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
        explicit RectangleProperties(std::size_t length, std::size_t width, std::size_t height) : AbstractProperties() { _length = length; _width = width; _height = height;};
        explicit RectangleProperties(JsonObject *obj) : AbstractProperties(obj) { _length = obj->getInt("length");
            _width = obj->getInt("width"); _height = obj->getInt("height");};
        ~RectangleProperties() override = default;
        std::size_t getLength() const { return _length; }
        std::size_t &getLength() { return _length; }
        std::size_t getWidth() const { return _width; }
        std::size_t &getWidth() { return _width; }
        std::size_t getHeight() const { return _height; }
        std::size_t &getHeight() { return _height; }
        void setLength(std::size_t length) { _length = length; }
        void setWidth(std::size_t width) { _width = width; }
        void setHeight(std::size_t height) { _height = height; }
    protected:
        std::size_t _length;
        std::size_t _width;
        std::size_t _height;
};
