/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <cstddef>
#include "primitives/Properties/ConeProperties.hpp"
#include "Object.hpp"
#include "json/Json.hpp"

class Cone : public Object {
public:
    Cone();
    Cone(const Material &material, const Transform &transform, const std::vector<Texture> &textures, float radius, float height);
    Cone(const Material &material, const Transform &transform, const std::vector<Texture> &textures, const ConeProperties &properties);
    Cone(const Cone &other);
    explicit Cone(JsonObject *obj);
    Cone(ConeProperties &cylinder);
    ~Cone() override = default;
    [[nodiscard]] ConeProperties getProperties() const;
    [[nodiscard]] ConeProperties &getProperties();
    void setProperties(ConeProperties &properties);
protected:
    ConeProperties _properties;
};
