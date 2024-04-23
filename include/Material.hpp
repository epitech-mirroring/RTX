/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <SFML/Graphics/Color.hpp>

class Material {
protected:
    sf::Color _color;
    sf::Color _emission;
    float _brightness;
    float _roughness;
    float _opacity;
    //TODO: Diffraction
};
