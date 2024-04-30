/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Material.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include <vector>

class Object {
protected:
    Material _material;
    Transform _transform;
    unsigned int _vao;
    unsigned int _vbo;
    unsigned int _ebo;
public:
    Object();
    Object(const Material& material, const Transform &transform, const std::vector<float> &vertices, const std::vector<std::size_t> &indices, const std::vector<Texture> &textures);
    Object(const Object &other);
    ~Object();

    Transform &getTransform();
    [[nodiscard]] Transform getTransform() const;
    Material &getMaterial();
    [[nodiscard]] Material getMaterial() const;

    [[nodiscard]] unsigned int getVao() const;

    void setTransform(const Transform &transform);
    void setMaterial(const Material &material);
};
