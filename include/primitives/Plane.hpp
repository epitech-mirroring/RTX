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
    ~Plane() override = default;
    void setProperties(PlaneProperties *properties);
    [[nodiscard]] PlaneProperties *getProperties() const;
    [[nodiscard]] PlaneProperties *getProperties();
protected:
    PlaneProperties *_properties;
};
