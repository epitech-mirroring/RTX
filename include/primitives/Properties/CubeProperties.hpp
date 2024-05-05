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

class CubeProperties : public AbstractProperties {
public:
    CubeProperties() : AbstractProperties() { _size = 1.0; };
    explicit CubeProperties(float size) : AbstractProperties() { _size = size; };
    explicit CubeProperties(JsonObject *obj) : AbstractProperties(obj) { _size = obj->getFloat("size");};
    ~CubeProperties() override = default;
    [[nodiscard]] float getSize() const { return _size; }
    [[nodiscard]] float &getSize() { return _size; }
    void setSize(float size) { _size = size; }
protected:
    float _size;
};
