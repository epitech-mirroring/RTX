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
#include "GLSL/Vertex.hpp"

Test(Vertex, Constructor)
{
    GLSL::Vertex vertex;
    cr_assert_eq(vertex.getPosition().x(), 0.0);
    cr_assert_eq(vertex.getPosition().y(), 0.0);
    cr_assert_eq(vertex.getPosition().z(), 0.0);
    cr_assert_eq(vertex.getNormal().x(), 0.0);
    cr_assert_eq(vertex.getNormal().y(), 0.0);
    cr_assert_eq(vertex.getNormal().z(), 0.0);
    cr_assert_eq(vertex.getUV().x(), 0.0);
    cr_assert_eq(vertex.getUV().y(), 0.0);
}

Test(Vertex, ConstructorWithArgs)
{
    GLSL::Vertex vertex(GLSL::Vector<3>(1.0, 2.0, 3.0), GLSL::Vector<3>(4.0, 5.0, 6.0), GLSL::Vector<2>(7.0, 8.0));
    cr_assert_eq(vertex.getPosition().x(), 1.0);
    cr_assert_eq(vertex.getPosition().y(), 2.0);
    cr_assert_eq(vertex.getPosition().z(), 3.0);
    cr_assert_eq(vertex.getNormal().x(), 4.0);
    cr_assert_eq(vertex.getNormal().y(), 5.0);
    cr_assert_eq(vertex.getNormal().z(), 6.0);
    cr_assert_eq(vertex.getUV().x(), 7);
    cr_assert_eq(vertex.getUV().y(), 8.0);
}

Test(Vertex, CopyConstructor)
{
    GLSL::Vertex vertex(GLSL::Vector<3>(1.0, 2.0, 3.0), GLSL::Vector<3>(4.0, 5.0, 6.0), GLSL::Vector<2>(7.0, 8.0));
    const GLSL::Vertex& vertex2(vertex);
    cr_assert_eq(vertex2.getPosition().x(), 1.0);
    cr_assert_eq(vertex2.getPosition().y(), 2.0);
    cr_assert_eq(vertex2.getPosition().z(), 3.0);
    cr_assert_eq(vertex2.getNormal().x(), 4.0);
    cr_assert_eq(vertex2.getNormal().y(), 5.0);
    cr_assert_eq(vertex2.getNormal().z(), 6.0);
    cr_assert_eq(vertex2.getUV().x(), 7);
    cr_assert_eq(vertex2.getUV().y(), 8.0);
}

Test(Vertex, Setters)
{
    GLSL::Vertex vertex;
    vertex.setPosition(GLSL::Vector<3>(1.0, 2.0, 3.0));
    vertex.setNormal(GLSL::Vector<3>(4.0, 5.0, 6.0));
    vertex.setUV(GLSL::Vector<2>(7.0, 8.0));
    cr_assert_eq(vertex.getPosition().x(), 1.0);
    cr_assert_eq(vertex.getPosition().y(), 2.0);
    cr_assert_eq(vertex.getPosition().z(), 3.0);
    cr_assert_eq(vertex.getNormal().x(), 4.0);
    cr_assert_eq(vertex.getNormal().y(), 5.0);
    cr_assert_eq(vertex.getNormal().z(), 6.0);
    cr_assert_eq(vertex.getUV().x(), 7);
    cr_assert_eq(vertex.getUV().y(), 8.0);
}

Test(Vertex, Getters)
{
    GLSL::Vertex vertex(GLSL::Vector<3>(1.0, 2.0, 3.0), GLSL::Vector<3>(4.0, 5.0, 6.0), GLSL::Vector<2>(7.0, 8.0));
    cr_assert_eq(vertex.getPosition().x(), 1.0);
    cr_assert_eq(vertex.getPosition().y(), 2.0);
    cr_assert_eq(vertex.getPosition().z(), 3.0);
    cr_assert_eq(vertex.getNormal().x(), 4.0);
    cr_assert_eq(vertex.getNormal().y(), 5.0);
    cr_assert_eq(vertex.getNormal().z(), 6.0);
    cr_assert_eq(vertex.getUV().x(), 7);
    cr_assert_eq(vertex.getUV().y(), 8.0);
}

Test(Vertex, GetPosition)
{
    GLSL::Vertex vertex(GLSL::Vector<3>(1.0, 2.0, 3.0), GLSL::Vector<3>(4.0, 5.0, 6.0), GLSL::Vector<2>(7.0, 8.0));
    cr_assert_eq(vertex.getPosition().x(), 1.0);
    cr_assert_eq(vertex.getPosition().y(), 2.0);
    cr_assert_eq(vertex.getPosition().z(), 3.0);
}

Test(Vertex, GetNormal)
{
    GLSL::Vertex vertex(GLSL::Vector<3>(1.0, 2.0, 3.0), GLSL::Vector<3>(4.0, 5.0, 6.0), GLSL::Vector<2>(7.0, 8.0));
    cr_assert_eq(vertex.getNormal().x(), 4.0);
    cr_assert_eq(vertex.getNormal().y(), 5.0);
    cr_assert_eq(vertex.getNormal().z(), 6.0);
}

Test(Vertex, GetUV)
{
    GLSL::Vertex vertex(GLSL::Vector<3>(1.0, 2.0, 3.0), GLSL::Vector<3>(4.0, 5.0, 6.0), GLSL::Vector<2>(7.0, 8.0));
    cr_assert_eq(vertex.getUV().x(), 7);
    cr_assert_eq(vertex.getUV().y(), 8.0);
}

Test(Vertex, SetPosition)
{
    GLSL::Vertex vertex;
    vertex.setPosition(GLSL::Vector<3>(1.0, 2.0, 3.0));
    cr_assert_eq(vertex.getPosition().x(), 1.0);
    cr_assert_eq(vertex.getPosition().y(), 2.0);
    cr_assert_eq(vertex.getPosition().z(), 3.0);
}

Test(Vertex, SetNormal)
{
    GLSL::Vertex vertex;
    vertex.setNormal(GLSL::Vector<3>(4.0, 5.0, 6.0));
    cr_assert_eq(vertex.getNormal().x(), 4.0);
    cr_assert_eq(vertex.getNormal().y(), 5.0);
    cr_assert_eq(vertex.getNormal().z(), 6.0);
}

Test(Vertex, SetUV)
{
    GLSL::Vertex vertex;
    vertex.setUV(GLSL::Vector<2>(7.0, 8.0));
    cr_assert_eq(vertex.getUV().x(), 7);
    cr_assert_eq(vertex.getUV().y(), 8.0);
}
