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
#include "GLSL/Color.hpp"

Test(Color, Constructor)
{
    GLSL::Color color = GLSL::Color(0.0, 0.0, 0.0);
    cr_assert_eq(color.getR(), 0.0);
    cr_assert_eq(color.getG(), 0.0);
    cr_assert_eq(color.getB(), 0.0);
    cr_assert_eq(color.getA(), 255.0);
}

Test(Color, Constructor2)
{
    GLSL::Color color = GLSL::Color(0.0, 0.0, 0.0, 0.0);
    cr_assert_eq(color.getR(), 0.0);
    cr_assert_eq(color.getG(), 0.0);
    cr_assert_eq(color.getB(), 0.0);
    cr_assert_eq(color.getA(), 0.0);
}

Test(Color, Constructor3)
{
    GLSL::Color color = GLSL::Color(0.0, 0.0, 0.0, 0.0);
    GLSL::Color color2 = GLSL::Color(color);
    cr_assert_eq(color2.getR(), 0.0);
    cr_assert_eq(color2.getG(), 0.0);
    cr_assert_eq(color2.getB(), 0.0);
    cr_assert_eq(color2.getA(), 0.0);
}

Test(Color, emptyConstructor)
{
    GLSL::Color color = GLSL::Color();
    cr_assert_eq(color.getR(), 0.0);
    cr_assert_eq(color.getG(), 0.0);
    cr_assert_eq(color.getB(), 0.0);
    cr_assert_eq(color.getA(), 255.0);
}

Test(Color, setR)
{
    GLSL::Color color = GLSL::Color();
    color.setR(0.5);
    cr_assert_eq(color.getR(), 0.5);
}

Test(Color, setG)
{
    GLSL::Color color = GLSL::Color();
    color.setG(0.5);
    cr_assert_eq(color.getG(), 0.5);
}

Test(Color, setB)
{
    GLSL::Color color = GLSL::Color();
    color.setB(0.5);
    cr_assert_eq(color.getB(), 0.5);
}

Test(Color, setA)
{
    GLSL::Color color = GLSL::Color();
    color.setA(0.5);
    cr_assert_eq(color.getA(), 0.5);
}

Test(Color, constGetR)
{
    const GLSL::Color color = GLSL::Color(0.5, 0.0, 0.0);
    cr_assert_eq(color.getR(), 0.5);
}

Test(Color, constGetG)
{
    const GLSL::Color color = GLSL::Color(0.0, 0.5, 0.0);
    cr_assert_eq(color.getG(), 0.5);
}

Test(Color, constGetB)
{
    const GLSL::Color color = GLSL::Color(0.0, 0.0, 0.5);
    cr_assert_eq(color.getB(), 0.5);
}

Test(Color, constGetA)
{
    const GLSL::Color color = GLSL::Color(0.0, 0.0, 0.0, 0.5);
    cr_assert_eq(color.getA(), 0.5);
}
