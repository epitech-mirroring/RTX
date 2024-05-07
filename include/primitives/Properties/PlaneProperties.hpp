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

class PlaneProperties : public AbstractProperties {
public:
    PlaneProperties();
    explicit PlaneProperties(float height, float width);
    explicit PlaneProperties(JsonObject *obj);
    ~PlaneProperties() override = default;
    float getHeight() const;
    float &getHeight();
    float getWidth() const;
    float &getWidth();
    void setHeight(float height);
    void setWidth(float width);
protected:
    float _height;
    float _width;
};
