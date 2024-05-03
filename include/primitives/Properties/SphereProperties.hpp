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
        SphereProperties() : AbstractProperties() { _radius = 1; };
        explicit SphereProperties(std::size_t radius) : AbstractProperties() { _radius = radius; };
        explicit SphereProperties(JsonObject *obj) : AbstractProperties(obj) { _radius = obj->getInt("radius");};
        ~SphereProperties() override = default;
        [[nodiscard]] std::size_t getRadius() const { return _radius; }
        [[nodiscard]] std::size_t &getRadius() { return _radius; }
        void setRadius(std::size_t radius) { _radius = radius; }
    protected:
        std::size_t _radius;
};
