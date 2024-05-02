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
    _color = glm::vec3(0.0, 0.0, 0.0);
    _emission = glm::vec3(0.0, 0.0, 0.0);
    _brightness = 0.0;
    _roughness = 0.0;
}

Material::Material(const glm::vec3 &color, const glm::vec3 &emission, const double brightness, const double roughness)
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

glm::vec3 Material::getColor() const
{
    return _color;
}

glm::vec3  Material::getEmission() const
{
    return _emission;
}

glm::vec3  &Material::getColor()
{
    return _color;
}

glm::vec3  &Material::getEmission()
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

void Material::setColor(const glm::vec3 &color)
{
    _color = color;
}

void Material::setEmission(const glm::vec3 &emission)
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
