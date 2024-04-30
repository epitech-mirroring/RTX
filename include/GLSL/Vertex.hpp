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
    class Vertex {
    private:
        Vector<3> _position;
        Vector<3> _normal;
        Vector<2> _uv;
    public:
        Vertex();
        Vertex(const Vector<3>& position, const Vector<3>& normal, const Vector<2>& uv);
        Vertex(const Vertex &other);
        ~Vertex() = default;

        [[nodiscard]] Vector<3> getPosition() const;
        [[nodiscard]] Vector<3> getNormal() const;
        [[nodiscard]] Vector<2> getUV() const;

        void setPosition(const Vector<3>& position);
        void setNormal(const Vector<3>& normal);
        void setUV(const Vector<2>& uv);
    };
}
