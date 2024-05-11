/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <cstddef>
#include "primitives/Properties/TorusProperties.hpp"
#include "Object.hpp"
#include "json/Json.hpp"

class Torus : public Object {
public:
    Torus();
    Torus(const Material &material, const Transform &transform, const std::vector<Texture> &textures, float radius, float height);
    Torus(const Material &material, const Transform &transform, const std::vector<Texture> &textures, const TorusProperties &properties);
    Torus(const Torus &other);
    explicit Torus(JsonObject *obj);
    Torus(TorusProperties &cylinder);
    ~Torus() override = default;
    [[nodiscard]] TorusProperties getProperties() const;
    [[nodiscard]] TorusProperties &getProperties();
    void setProperties(TorusProperties &properties);
protected:
    TorusProperties _properties;
};
