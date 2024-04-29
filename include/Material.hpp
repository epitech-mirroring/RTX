/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "GLSL/Color.hpp"

namespace GLSL {
    class Material {
    protected:
        Color _color;
        Color _emission;
        double _brightness;
        double _roughness;
    public:
        Material();
        Material(const Color &color, const Color &emission, const double brightness, const double roughness);
        Material(const Material &material);
        ~Material() = default;
        [[nodiscard]] Color getColor() const;
        [[nodiscard]] Color getEmission() const;
        [[nodiscard]] Color &getColor();
        [[nodiscard]] Color &getEmission();
        [[nodiscard]] double getBrightness() const;
        [[nodiscard]] double &getBrightness();
        [[nodiscard]] double getRoughness() const;
        [[nodiscard]] double &getRoughness();
        void setColor(const Color &color);
        void setEmission(const Color &emission);
        void setBrightness(const double brightness);
        void setRoughness(const double roughness);
        //TODO: Diffraction
    };
}
