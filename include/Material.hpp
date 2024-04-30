/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "GLSL/Color.hpp"

class Material {
protected:
    GLSL::Color _color;
    GLSL::Color _emission;
    double _brightness;
    double _roughness;
public:
    Material();
    Material(const GLSL::Color &color, const GLSL::Color &emission, double brightness, double roughness);
    Material(const Material &material);
    ~Material() = default;
    [[nodiscard]] GLSL::Color getColor() const;
    [[nodiscard]] GLSL::Color getEmission() const;
    [[nodiscard]] GLSL::Color &getColor();
    [[nodiscard]] GLSL::Color &getEmission();
    [[nodiscard]] double getBrightness() const;
    [[nodiscard]] double &getBrightness();
    [[nodiscard]] double getRoughness() const;
    [[nodiscard]] double &getRoughness();
    void setColor(const GLSL::Color &color);
    void setEmission(const GLSL::Color &emission);
    void setBrightness(double brightness);
    void setRoughness(double roughness);
    //TODO: Diffraction
};
