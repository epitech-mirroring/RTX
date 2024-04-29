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
        Vertex() {
            _position = Vector<3>(0.0, 0.0, 0.0);
            _normal = Vector<3>(0.0, 0.0, 0.0);
            _uv = Vector<2>(0.0, 0.0);
        };
        Vertex(const Vector<3>& position, const Vector<3>& normal, const Vector<2>& uv) {
            _position = position;
            _normal = normal;
            _uv = uv;
        };
        Vertex(const Vertex &other) {
            _position = other.GetPosition();
            _normal = other.GetNormal();
            _uv = other.GetUV();
        };
        ~Vertex() = default;

        [[nodiscard]] Vector<3> GetPosition() const {
            return _position;
        };
        [[nodiscard]] Vector<3> GetNormal() const {
            return _normal;
        };
        [[nodiscard]] Vector<2> GetUV() const {
            return _uv;
        };

        void SetPosition(const Vector<3>& position) {
            _position = position;
        };
        void SetNormal(const Vector<3>& normal) {
            _normal = normal;
        };
        void SetUV(const Vector<2>& uv) {
            _uv = uv;
        };
    };
}
