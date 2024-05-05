/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Object.hpp"
#include "json/Json.hpp"
#include "primitives/Properties/CubeProperties.hpp"

class Cube : public Object {
public:
    Cube();
    Cube(const Material& material, const Transform& transform, const std::vector<Texture>& textures, float size);
    Cube(const Material& material, const Transform& transform, const std::vector<Texture>& textures, const CubeProperties& properties);
    Cube(const Cube &other);
    explicit Cube(JsonObject *obj);
    explicit Cube(CubeProperties &properties);
    ~Cube() override = default;

    [[nodiscard]] CubeProperties getProperties() const;
    [[nodiscard]] CubeProperties &getProperties();
    float getSize() const { return _properties.getSize(); }
    float &getSize() { return _properties.getSize(); }
protected:
    CubeProperties _properties{};
};
