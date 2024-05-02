/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <vector>
#include "GLSL/Shader.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include <functional>

class Object {
protected:
    Material _material;
    Transform _transform;
    unsigned int _vao;
    unsigned int _vbo;
    unsigned int _ebo;
    unsigned int _faceCount;
public:
    Object();
    Object(const Material& material, const Transform &transform, const std::vector<glm::vec3> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture> &textures);
    Object(const Object &other);
    ~Object();

    Transform &getTransform();
    [[nodiscard]] Transform getTransform() const;
    Material &getMaterial();
    [[nodiscard]] Material getMaterial() const;

    [[nodiscard]] unsigned int getVao() const;

    void setTransform(const Transform &transform);
    void setMaterial(const Material &material);

    void bind() const;
    void unbind() const;
    void draw() const;
    void draw(const GLSL::Shader &vertexShader, const GLSL::Shader &fragmentShader, std::function<void(const GLSL::Shader &vertexShader, const GLSL::Shader &fragmentShader)> uniforms = nullptr) const;
};
