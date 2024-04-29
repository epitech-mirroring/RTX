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
    cr_assert_eq(vertex.GetPosition().x(), 0.0);
    cr_assert_eq(vertex.GetPosition().y(), 0.0);
    cr_assert_eq(vertex.GetPosition().z(), 0.0);
    cr_assert_eq(vertex.GetNormal().x(), 0.0);
    cr_assert_eq(vertex.GetNormal().y(), 0.0);
    cr_assert_eq(vertex.GetNormal().z(), 0.0);
    cr_assert_eq(vertex.GetUV().x(), 0.0);
    cr_assert_eq(vertex.GetUV().y(), 0.0);
}

Test(Vertex, ConstructorWithArgs)
{
    GLSL::Vertex vertex(GLSL::Vector<3>(1.0, 2.0, 3.0), GLSL::Vector<3>(4.0, 5.0, 6.0), GLSL::Vector<2>(7.0, 8.0));
    cr_assert_eq(vertex.GetPosition().x(), 1.0);
    cr_assert_eq(vertex.GetPosition().y(), 2.0);
    cr_assert_eq(vertex.GetPosition().z(), 3.0);
    cr_assert_eq(vertex.GetNormal().x(), 4.0);
    cr_assert_eq(vertex.GetNormal().y(), 5.0);
    cr_assert_eq(vertex.GetNormal().z(), 6.0);
    cr_assert_eq(vertex.GetUV().x(), 7);
    cr_assert_eq(vertex.GetUV().y(), 8.0);
}

Test(Vertex, CopyConstructor)
{
    GLSL::Vertex vertex(GLSL::Vector<3>(1.0, 2.0, 3.0), GLSL::Vector<3>(4.0, 5.0, 6.0), GLSL::Vector<2>(7.0, 8.0));
    const GLSL::Vertex& vertex2(vertex);
    cr_assert_eq(vertex2.GetPosition().x(), 1.0);
    cr_assert_eq(vertex2.GetPosition().y(), 2.0);
    cr_assert_eq(vertex2.GetPosition().z(), 3.0);
    cr_assert_eq(vertex2.GetNormal().x(), 4.0);
    cr_assert_eq(vertex2.GetNormal().y(), 5.0);
    cr_assert_eq(vertex2.GetNormal().z(), 6.0);
    cr_assert_eq(vertex2.GetUV().x(), 7);
    cr_assert_eq(vertex2.GetUV().y(), 8.0);
}

Test(Vertex, Setters)
{
    GLSL::Vertex vertex;
    vertex.SetPosition(GLSL::Vector<3>(1.0, 2.0, 3.0));
    vertex.SetNormal(GLSL::Vector<3>(4.0, 5.0, 6.0));
    vertex.SetUV(GLSL::Vector<2>(7.0, 8.0));
    cr_assert_eq(vertex.GetPosition().x(), 1.0);
    cr_assert_eq(vertex.GetPosition().y(), 2.0);
    cr_assert_eq(vertex.GetPosition().z(), 3.0);
    cr_assert_eq(vertex.GetNormal().x(), 4.0);
    cr_assert_eq(vertex.GetNormal().y(), 5.0);
    cr_assert_eq(vertex.GetNormal().z(), 6.0);
    cr_assert_eq(vertex.GetUV().x(), 7);
    cr_assert_eq(vertex.GetUV().y(), 8.0);
}

Test(Vertex, Getters)
{
    GLSL::Vertex vertex(GLSL::Vector<3>(1.0, 2.0, 3.0), GLSL::Vector<3>(4.0, 5.0, 6.0), GLSL::Vector<2>(7.0, 8.0));
    cr_assert_eq(vertex.GetPosition().x(), 1.0);
    cr_assert_eq(vertex.GetPosition().y(), 2.0);
    cr_assert_eq(vertex.GetPosition().z(), 3.0);
    cr_assert_eq(vertex.GetNormal().x(), 4.0);
    cr_assert_eq(vertex.GetNormal().y(), 5.0);
    cr_assert_eq(vertex.GetNormal().z(), 6.0);
    cr_assert_eq(vertex.GetUV().x(), 7);
    cr_assert_eq(vertex.GetUV().y(), 8.0);
}

Test(Vertex, GetPosition)
{
    GLSL::Vertex vertex(GLSL::Vector<3>(1.0, 2.0, 3.0), GLSL::Vector<3>(4.0, 5.0, 6.0), GLSL::Vector<2>(7.0, 8.0));
    cr_assert_eq(vertex.GetPosition().x(), 1.0);
    cr_assert_eq(vertex.GetPosition().y(), 2.0);
    cr_assert_eq(vertex.GetPosition().z(), 3.0);
}

Test(Vertex, GetNormal)
{
    GLSL::Vertex vertex(GLSL::Vector<3>(1.0, 2.0, 3.0), GLSL::Vector<3>(4.0, 5.0, 6.0), GLSL::Vector<2>(7.0, 8.0));
    cr_assert_eq(vertex.GetNormal().x(), 4.0);
    cr_assert_eq(vertex.GetNormal().y(), 5.0);
    cr_assert_eq(vertex.GetNormal().z(), 6.0);
}

Test(Vertex, GetUV)
{
    GLSL::Vertex vertex(GLSL::Vector<3>(1.0, 2.0, 3.0), GLSL::Vector<3>(4.0, 5.0, 6.0), GLSL::Vector<2>(7.0, 8.0));
    cr_assert_eq(vertex.GetUV().x(), 7);
    cr_assert_eq(vertex.GetUV().y(), 8.0);
}

Test(Vertex, SetPosition)
{
    GLSL::Vertex vertex;
    vertex.SetPosition(GLSL::Vector<3>(1.0, 2.0, 3.0));
    cr_assert_eq(vertex.GetPosition().x(), 1.0);
    cr_assert_eq(vertex.GetPosition().y(), 2.0);
    cr_assert_eq(vertex.GetPosition().z(), 3.0);
}

Test(Vertex, SetNormal)
{
    GLSL::Vertex vertex;
    vertex.SetNormal(GLSL::Vector<3>(4.0, 5.0, 6.0));
    cr_assert_eq(vertex.GetNormal().x(), 4.0);
    cr_assert_eq(vertex.GetNormal().y(), 5.0);
    cr_assert_eq(vertex.GetNormal().z(), 6.0);
}

Test(Vertex, SetUV)
{
    GLSL::Vertex vertex;
    vertex.SetUV(GLSL::Vector<2>(7.0, 8.0));
    cr_assert_eq(vertex.GetUV().x(), 7);
    cr_assert_eq(vertex.GetUV().y(), 8.0);
}
