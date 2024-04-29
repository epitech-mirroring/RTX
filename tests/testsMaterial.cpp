/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include "Material.hpp"

Test(Material, Constructor)
{
    Material material = Material();
    cr_assert_eq(material.getColor().getR(), 0.0);
    cr_assert_eq(material.getColor().getG(), 0.0);
    cr_assert_eq(material.getColor().getB(), 0.0);
    cr_assert_eq(material.getColor().getA(), 255.0);
    cr_assert_eq(material.getEmission().getR(), 0.0);
    cr_assert_eq(material.getEmission().getG(), 0.0);
    cr_assert_eq(material.getEmission().getB(), 0.0);
    cr_assert_eq(material.getEmission().getA(), 255.0);
    cr_assert_eq(material.getBrightness(), 0.0);
    cr_assert_eq(material.getRoughness(), 0.0);
}

Test(Material, Constructor2)
{
    Material material = Material(GLSL::Color(0.0, 0.0, 0.0), GLSL::Color(0.0, 0.0, 0.0), 0.0, 0.0);
    cr_assert_eq(material.getColor().getR(), 0.0);
    cr_assert_eq(material.getColor().getG(), 0.0);
    cr_assert_eq(material.getColor().getB(), 0.0);
    cr_assert_eq(material.getColor().getA(), 255.0);
    cr_assert_eq(material.getEmission().getR(), 0.0);
    cr_assert_eq(material.getEmission().getG(), 0.0);
    cr_assert_eq(material.getEmission().getB(), 0.0);
    cr_assert_eq(material.getEmission().getA(), 255.0);
    cr_assert_eq(material.getBrightness(), 0.0);
    cr_assert_eq(material.getRoughness(), 0.0);
}

Test(Material, Constructor3)
{
    Material material = Material(GLSL::Color(0.0, 0.0, 0.0), GLSL::Color(0.0, 0.0, 0.0), 0.0, 0.0);
    auto material2 = Material(material);
    cr_assert_eq(material2.getColor().getR(), 0.0);
    cr_assert_eq(material2.getColor().getG(), 0.0);
    cr_assert_eq(material2.getColor().getB(), 0.0);
    cr_assert_eq(material2.getColor().getA(), 255.0);
    cr_assert_eq(material2.getEmission().getR(), 0.0);
    cr_assert_eq(material2.getEmission().getG(), 0.0);
    cr_assert_eq(material2.getEmission().getB(), 0.0);
    cr_assert_eq(material2.getEmission().getA(), 255.0);
    cr_assert_eq(material2.getBrightness(), 0.0);
    cr_assert_eq(material2.getRoughness(), 0.0);
}

Test(Material, setColor)
{
    Material material = Material();
    material.setColor(GLSL::Color(1.0, 1.0, 1.0));
    cr_assert_eq(material.getColor().getR(), 1.0);
    cr_assert_eq(material.getColor().getG(), 1.0);
    cr_assert_eq(material.getColor().getB(), 1.0);
    cr_assert_eq(material.getColor().getA(), 255.0);
}

Test(Material, setEmission)
{
    Material material = Material();
    material.setEmission(GLSL::Color(1.0, 1.0, 1.0));
    cr_assert_eq(material.getEmission().getR(), 1.0);
    cr_assert_eq(material.getEmission().getG(), 1.0);
    cr_assert_eq(material.getEmission().getB(), 1.0);
    cr_assert_eq(material.getEmission().getA(), 255.0);
}

Test(Material, setBrightness)
{
    Material material = Material();
    material.setBrightness(1.0);
    cr_assert_eq(material.getBrightness(), 1.0);
}

Test(Material, setRoughness)
{
    Material material = Material();
    material.setRoughness(1.0);
    cr_assert_eq(material.getRoughness(), 1.0);
}

Test(Material, constGetColor)
{
    const Material material = Material();
    cr_assert_eq(material.getColor().getR(), 0.0);
    cr_assert_eq(material.getColor().getG(), 0.0);
    cr_assert_eq(material.getColor().getB(), 0.0);
    cr_assert_eq(material.getColor().getA(), 255.0);
}

Test(Material, constGetEmission)
{
    const Material material = Material();
    cr_assert_eq(material.getEmission().getR(), 0.0);
    cr_assert_eq(material.getEmission().getG(), 0.0);
    cr_assert_eq(material.getEmission().getB(), 0.0);
    cr_assert_eq(material.getEmission().getA(), 255.0);
}

Test(Material, constGetBrightness)
{
    const Material material = Material();
    cr_assert_eq(material.getBrightness(), 0.0);
}

Test(Material, constGetRoughness)
{
    const Material material = Material();
    cr_assert_eq(material.getRoughness(), 0.0);
}
