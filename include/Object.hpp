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
#include "GLSL/Vector.hpp"
#include "GLSL/Vertex.hpp"
#include "Transform.hpp"
#include <vector>
#include <unordered_map>

class Object {
protected:
    Material _material;
    Transform _transform;
    std::vector<GLSL::Vertex> _vertices;
    std::vector<unsigned int> _indices;
    std::unordered_map<Texture::TextureType, Texture> _textures;
public:
    Object();
    Object(Material material, Transform transform, std::vector<GLSL::Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    Object(const Object &other);
    ~Object();

    Transform &GetTransform();

    const Material &GetMaterial() const;
    const Transform &GetTransform() const;
    const GLSL::Vector<3> &GetPosition() const;
    const GLSL::Vector<3> &GetRotation() const;
    const GLSL::Vector<3> &GetScale() const;
    const std::vector<GLSL::Vertex> &GetVertices() const;
    const std::vector<unsigned int> &GetIndices() const;
    const std::vector<Texture> &GetTextures() const;
    const Texture &GetTexture(Texture::TextureType type) const;

    void SetTransform(Transform transform);
    void SetMaterial(Material material);
    void SetPosition(GLSL::Vector<3> position);
    void SetRotation(GLSL::Vector<3> rotation);
    void SetScale(GLSL::Vector<3> scale);
    void SetVertices(std::vector<GLSL::Vertex> vertices);
    void SetIndices(std::vector<unsigned int> indices);
    void SetTextures(std::vector<Texture> textures);
    void SetTextures(std::unordered_map<Texture::TextureType, Texture> textures);
    void SetTexture(Texture texture);
};
