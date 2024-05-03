/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "json/Json.hpp"
#include "glm/glm.hpp"
#include "GlmParser.hpp"

class Material {
protected:
    glm::vec3 _color;
    glm::vec3 _emission;
    double _brightness;
    double _roughness;
public:
    Material();
    Material(const glm::vec3 &color, const glm::vec3 &emission, double brightness, double roughness);
    Material(const Material &material);
    explicit Material(JsonObject *obj);
    ~Material() = default;
    [[nodiscard]] glm::vec3 getColor() const;
    [[nodiscard]] glm::vec3 getEmission() const;
    [[nodiscard]] glm::vec3 &getColor();
    [[nodiscard]] glm::vec3 &getEmission();
    [[nodiscard]] double getBrightness() const;
    [[nodiscard]] double &getBrightness();
    [[nodiscard]] double getRoughness() const;
    [[nodiscard]] double &getRoughness();
    void setColor(const glm::vec3 &color);
    void setEmission(const glm::vec3 &emission);
    void setBrightness(double brightness);
    void setRoughness(double roughness);
    //TODO: Diffraction
};
