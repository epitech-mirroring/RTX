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

class CylinderProperties : public AbstractProperties {
    public:
        CylinderProperties();
        CylinderProperties(float radius, float height);
        explicit CylinderProperties(JsonObject *obj);
        ~CylinderProperties() override = default;

        void SetRadius(float radius);
        void SetHeight(float height);
        float GetRadius() const;
        float GetHeight() const;
        float &GetRadius();
        float &GetHeight();
    private:
        float _radius;
        float _height;
};
