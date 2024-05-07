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

class PlaneProperties : public AbstractProperties {
public:
    PlaneProperties();
    explicit PlaneProperties(glm::vec3 axes);
    explicit PlaneProperties(JsonObject *obj);
    ~PlaneProperties() override = default;
    [[nodiscard]] glm::vec3 getAxes() const;
    [[nodiscard]] glm::vec3 &getAxes();
    void setAxes(glm::vec3 size);
protected:
    glm::vec3 _axes{};
};
