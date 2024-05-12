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

class TorusProperties : public AbstractProperties {
public:
    TorusProperties();
    TorusProperties(float radius, float middleRadius);
    explicit TorusProperties(JsonObject *obj);
    ~TorusProperties() override = default;

    void SetRadius(float radius);
    void SetMiddleRadius(float middleRadius);
    float GetRadius() const;
    float GetMiddleRadius() const;
    float &GetRadius();
    float &GetMiddleRadius();
private:
    float _radius;
    float _middleRadius;
};
