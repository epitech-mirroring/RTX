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
    cr_assert_eq(material.getColor().x, 0.0);
    cr_assert_eq(material.getColor().y, 0.0);
    cr_assert_eq(material.getColor().z, 0.0);
    cr_assert_eq(material.getEmission().x, 0.0);
    cr_assert_eq(material.getEmission().y, 0.0);
    cr_assert_eq(material.getEmission().z, 0.0);
    cr_assert_eq(material.getBrightness(), 0.0);
    cr_assert_eq(material.getRoughness(), 0.0);
}

Test(Material, Constructor2)
{
    Material material = Material(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 0.0, 0.0, 0.0, 0.0);
    cr_assert_eq(material.getColor().x, 0.0);
    cr_assert_eq(material.getColor().y, 0.0);
    cr_assert_eq(material.getColor().z, 0.0);
    cr_assert_eq(material.getEmission().x, 0.0);
    cr_assert_eq(material.getEmission().y, 0.0);
    cr_assert_eq(material.getEmission().z, 0.0);
    cr_assert_eq(material.getBrightness(), 0.0);
    cr_assert_eq(material.getRoughness(), 0.0);
    cr_assert_eq(material.getTransparency(), 0.0);
    cr_assert_eq(material.getRefractionIndex(), 0.0);
}

Test(Material, Constructor3)
{
    Material material = Material(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 0.0, 0.0, 0.0, 0.0);
    auto material2 = Material(material);
    cr_assert_eq(material2.getColor().x, 0.0);
    cr_assert_eq(material2.getColor().y, 0.0);
    cr_assert_eq(material2.getColor().z, 0.0);
    cr_assert_eq(material2.getEmission().x, 0.0);
    cr_assert_eq(material2.getEmission().y, 0.0);
    cr_assert_eq(material2.getEmission().z, 0.0);
    cr_assert_eq(material2.getBrightness(), 0.0);
    cr_assert_eq(material2.getRoughness(), 0.0);
    cr_assert_eq(material2.getTransparency(), 0.0);
    cr_assert_eq(material2.getRefractionIndex(), 0.0);
}

Test(Material, setColor)
{
    Material material = Material();
    material.setColor(glm::vec3(1.0, 1.0, 1.0));
    cr_assert_eq(material.getColor().x, 1.0);
    cr_assert_eq(material.getColor().y, 1.0);
    cr_assert_eq(material.getColor().z, 1.0);
}

Test(Material, setEmission)
{
    Material material = Material();
    material.setEmission(glm::vec3(1.0, 1.0, 1.0));
    cr_assert_eq(material.getEmission().x, 1.0);
    cr_assert_eq(material.getEmission().y, 1.0);
    cr_assert_eq(material.getEmission().z, 1.0);
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
    cr_assert_eq(material.getColor().x, 0.0);
    cr_assert_eq(material.getColor().y, 0.0);
    cr_assert_eq(material.getColor().z, 0.0);
}

Test(Material, constGetEmission)
{
    const Material material = Material();
    cr_assert_eq(material.getEmission().x, 0.0);
    cr_assert_eq(material.getEmission().y, 0.0);
    cr_assert_eq(material.getEmission().z, 0.0);
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
