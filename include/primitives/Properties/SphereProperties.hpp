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

class SphereProperties : public AbstractProperties {
    public:
        SphereProperties() : AbstractProperties() { _radius = 1.0f; };
        explicit SphereProperties(float radius) : AbstractProperties() { _radius = radius;};
        explicit SphereProperties(JsonObject *obj) : AbstractProperties(obj) { _radius = (float)obj->getFloat("radius"); };
        ~SphereProperties() override = default;
        [[nodiscard]] float getRadius() const { return _radius; }
        [[nodiscard]] float &getRadius() { return _radius; }
        void setRadius(float radius) { _radius = radius; }
    protected:
        float _radius;
};
