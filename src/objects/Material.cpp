/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Material.hpp"

Material::Material()
{
    _color = GLSL::Color(0.0, 0.0, 0.0);
    _emission = GLSL::Color(0.0, 0.0, 0.0);
    _brightness = 0.0;
    _roughness = 0.0;
}

Material::Material(const GLSL::Color &color, const GLSL::Color &emission, const double brightness, const double roughness)
{
    _color = color;
    _emission = emission;
    _brightness = brightness;
    _roughness = roughness;
}

Material::Material(const Material &material)
{
    _color = material._color;
    _emission = material._emission;
    _brightness = material._brightness;
    _roughness = material._roughness;
}

GLSL::Color Material::getColor() const
{
    return _color;
}

GLSL::Color Material::getEmission() const
{
    return _emission;
}

GLSL::Color &Material::getColor()
{
    return _color;
}

GLSL::Color &Material::getEmission()
{
    return _emission;
}

double Material::getBrightness() const
{
    return _brightness;
}

double &Material::getBrightness()
{
    return _brightness;
}

double Material::getRoughness() const
{
    return _roughness;
}

double &Material::getRoughness()
{
    return _roughness;
}

void Material::setColor(const GLSL::Color &color)
{
    _color = color;
}

void Material::setEmission(const GLSL::Color &emission)
{
    _emission = emission;
}

void Material::setBrightness(const double brightness)
{
    _brightness = brightness;
}

void Material::setRoughness(const double roughness)
{
    _roughness = roughness;
}
