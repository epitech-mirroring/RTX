/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <iostream>
#include "Material.hpp"

Material::Material()
{
    _color = glm::vec3(0.0, 0.0, 0.0);
    _emission = glm::vec3(0.0, 0.0, 0.0);
    _brightness = 0.0;
    _roughness = 0.0;
    _transparency = 0.0;
    _refractionIndex = 0.0;
    _hasCheckerPattern = false;
}

Material::Material(const glm::vec3 &color, const glm::vec3 &emission, const double brightness, const double roughness, const double transparency, const double refractionIndex, const bool hasCheckerPattern)
{
    _color = color;
    _emission = emission;
    _brightness = brightness;
    _roughness = roughness;
    _transparency = transparency;
    _refractionIndex = refractionIndex;
    _hasCheckerPattern = hasCheckerPattern;
}

Material::Material(const Material &material)
{
    _color = material._color;
    _emission = material._emission;
    _brightness = material._brightness;
    _roughness = material._roughness;
    _transparency = material._transparency;
    _refractionIndex = material._refractionIndex;
    _hasCheckerPattern = material._hasCheckerPattern;
}

Material::Material(JsonObject *obj)
{
    _color = GlmParser::parseColor(obj->getValue<JsonObject>("color"));
    _emission = GlmParser::parseColor(obj->getValue<JsonObject>("emission"));
    _brightness = obj->getFloat("brightness");
    _roughness = obj->getFloat("roughness");
    try {
        _transparency = obj->getFloat("transparency");
    } catch (std::exception &e) {
        _transparency = 0.0;
    }
    try {
        _refractionIndex = obj->getFloat("refractionIndex");
    } catch (std::exception &e) {
        _refractionIndex = 0.0;
    }
    try {
        _hasCheckerPattern = obj->getBoolean("hasCheckerPattern");
    } catch (std::exception &e) {
        _hasCheckerPattern = false;
    }
}

glm::vec3 Material::getColor() const
{
    return _color;
}

glm::vec3 Material::getEmission() const
{
    return _emission;
}

glm::vec3 &Material::getColor()
{
    return _color;
}

glm::vec3 &Material::getEmission()
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

double Material::getTransparency() const
{
    return _transparency;
}

double &Material::getTransparency()
{
    return _transparency;
}

double Material::getRefractionIndex() const
{
    return _refractionIndex;
}

double &Material::getRefractionIndex()
{
    return _refractionIndex;
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

void Material::setTransparency(const double transparency)
{
    _transparency = transparency;
}

void Material::setRefractionIndex(const double refractionIndex)
{
    _refractionIndex = refractionIndex;
}

bool Material::hasCheckerPattern() const
{
    return _hasCheckerPattern;
}

bool &Material::hasCheckerPattern()
{
    return _hasCheckerPattern;
}

void Material::setHasCheckerPattern(const bool hasCheckerPattern)
{
    _hasCheckerPattern = hasCheckerPattern;
}
