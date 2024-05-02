/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "GLSL/Vector.hpp"
#include "json/Json.hpp"

namespace GLSL {
    class Color : public Vector<4> {
    public:
        Color();
        Color(double r, double g, double b, double a=255.0);
        Color(const Color &color);
        explicit Color(JsonObject *obj);
        ~Color() = default;
        [[nodiscard]] double getR() const;
        [[nodiscard]] double &getR();
        [[nodiscard]] double getG() const;
        [[nodiscard]] double &getG();
        [[nodiscard]] double getB() const;
        [[nodiscard]] double &getB();
        [[nodiscard]] double getA() const;
        [[nodiscard]] double &getA();
        void setR(double r);
        void setG(double g);
        void setB(double b);
        void setA(double a);
    };
}
