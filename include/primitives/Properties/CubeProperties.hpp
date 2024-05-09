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

class CubeProperties : public AbstractProperties {
public:
    CubeProperties();
    explicit CubeProperties(float size);
    explicit CubeProperties(JsonObject *obj);
    ~CubeProperties() override = default;
    [[nodiscard]] float getSize() const;
    [[nodiscard]] float &getSize();
    void setSize(float size);
protected:
    float _size;
};
