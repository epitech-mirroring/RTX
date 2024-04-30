/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** Camera.cpp
*/

#include "GLSL/Color.hpp"

GLSL::Color::Color()
{
    _data[0] = 0.0;
    _data[1] = 0.0;
    _data[2] = 0.0;
    _data[3] = 255.0;
}

GLSL::Color::Color(const double r, const double g, const double b, const double a)
{
    _data[0] = r;
    _data[1] = g;
    _data[2] = b;
    _data[3] = a;
}

GLSL::Color::Color(const Color &color) = default;

double GLSL::Color::getR() const
{
    return this->r();
}

double &GLSL::Color::getR()
{
    return this->_data[0];
}

double GLSL::Color::getG() const
{
    return this->g();
}

double &GLSL::Color::getG()
{
    return this->_data[1];
}

double GLSL::Color::getB() const
{
    return this->b();
}

double &GLSL::Color::getB()
{
    return this->_data[2];
}

double GLSL::Color::getA() const
{
    return this->a();
}

double &GLSL::Color::getA()
{
    return this->_data[3];
}

void GLSL::Color::setR(const double r)
{
    this->r() = r;
}

void GLSL::Color::setG(const double g)
{
    this->g() = g;
}

void GLSL::Color::setB(const double b)
{
    this->b() = b;
}

void GLSL::Color::setA(const double a)
{
    this->a() = a;
}
