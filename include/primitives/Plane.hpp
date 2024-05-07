/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <cstddef>
#include "Object.hpp"
#include "primitives/Properties/PlaneProperties.hpp"

class Plane : public Object {
public:
    Plane();
    explicit Plane(PlaneProperties *properties);
    Plane(const Material &material, const Transform &transform, const std::vector<Texture> &textures, float height, float width);
    ~Plane() override = default;
    [[nodiscard]] PlaneProperties *getProperties() const;
    [[nodiscard]] PlaneProperties *getProperties();
    void setProperties(PlaneProperties *properties);
protected:
    PlaneProperties *_properties{};
};
