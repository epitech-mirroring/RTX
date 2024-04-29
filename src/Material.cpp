/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Material.hpp"

GLSL::Material::Material()
{
    _color = Color(0.0, 0.0, 0.0);
    _emission = Color(0.0, 0.0, 0.0);
    _brightness = 0.0;
    _roughness = 0.0;
}

GLSL::Material::Material(const Color &color, const Color &emission, const double brightness, const double roughness)
{
    _color = color;
    _emission = emission;
    _brightness = brightness;
    _roughness = roughness;
}

GLSL::Material::Material(const Material &material)
{
    _color = material._color;
    _emission = material._emission;
    _brightness = material._brightness;
    _roughness = material._roughness;
}

GLSL::Color GLSL::Material::getColor() const
{
    return _color;
}

GLSL::Color GLSL::Material::getEmission() const
{
    return _emission;
}

GLSL::Color &GLSL::Material::getColor()
{
    return _color;
}

GLSL::Color &GLSL::Material::getEmission()
{
    return _emission;
}

double GLSL::Material::getBrightness() const
{
    return _brightness;
}

double &GLSL::Material::getBrightness()
{
    return _brightness;
}

double GLSL::Material::getRoughness() const
{
    return _roughness;
}

double &GLSL::Material::getRoughness()
{
    return _roughness;
}

void GLSL::Material::setColor(const Color &color)
{
    _color = color;
}

void GLSL::Material::setEmission(const Color &emission)
{
    _emission = emission;
}

void GLSL::Material::setBrightness(const double brightness)
{
    _brightness = brightness;
}

void GLSL::Material::setRoughness(const double roughness)
{
    _roughness = roughness;
}
