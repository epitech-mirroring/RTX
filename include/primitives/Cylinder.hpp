/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <cstddef>
#include "primitives/Properties/CylinderProperties.hpp"
#include "Object.hpp"
#include "json/Json.hpp"

class Cylinder : public Object {
public:
    Cylinder();
    Cylinder(const Material &material, const Transform &transform, const std::vector<Texture> &textures, float radius, float height);
    Cylinder(const Material &material, const Transform &transform, const std::vector<Texture> &textures, const CylinderProperties &properties);
    Cylinder(const Cylinder &other);
    explicit Cylinder(JsonObject *obj);
    Cylinder(CylinderProperties &cylinder);
    ~Cylinder() override = default;
    [[nodiscard]] CylinderProperties getProperties() const;
    [[nodiscard]] CylinderProperties &getProperties();
    void setProperties(CylinderProperties &properties);
protected:
    CylinderProperties _properties;
};
