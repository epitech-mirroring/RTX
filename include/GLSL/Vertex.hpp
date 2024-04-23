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
        Vertex(Vector<3> position, Vector<3> normal, Vector<2> uv);
        Vertex(const Vertex &other);
        ~Vertex();

        Vector<3> GetPosition() const;
        Vector<3> GetNormal() const;
        Vector<2> GetUV() const;

        void SetPosition(Vector<3> position);
        void SetNormal(Vector<3> normal);
        void SetUV(Vector<2> uv);
    };
}
