/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "GLSL/Vector.hpp"

namespace GLSL {
    class Color : public Vector<4> {
    public:
        Color();
        Color(const double r, const double g, const double b, const double a=255.0);
        Color(const Color &color);
        ~Color() = default;
        [[nodiscard]] double getR() const;
        [[nodiscard]] double &getR();
        [[nodiscard]] double getG() const;
        [[nodiscard]] double &getG();
        [[nodiscard]] double getB() const;
        [[nodiscard]] double &getB();
        [[nodiscard]] double getA() const;
        [[nodiscard]] double &getA();
        void setR(const double r);
        void setG(const double g);
        void setB(const double b);
        void setA(const double a);
    };
}
