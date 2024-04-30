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
    std::vector<std::size_t> _indices;
    std::unordered_map<Texture::TextureType, Texture> _textures;
public:
    Object();
    Object(Material material, Transform transform, std::vector<GLSL::Vertex> vertices, std::vector<std::size_t> indices, std::vector<Texture> textures);
    Object(const Object &other);
    ~Object() = default;

    Transform &getTransform();
    Transform getTransform() const;
    Material &getMaterial();
    Material getMaterial() const;
    std::vector<GLSL::Vertex> &getVertices();
    std::vector<GLSL::Vertex> getVertices() const;
    std::vector<std::size_t> &getIndices();
    std::vector<std::size_t> getIndices() const;
    std::vector<Texture> &getTextures();
    std::vector<Texture> getTextures() const;
    Texture &getTexture(Texture::TextureType type);
    Texture getTexture(Texture::TextureType type) const;

    void setTransform(Transform transform);
    void setMaterial(Material material);
    void setVertices(std::vector<GLSL::Vertex> vertices);
    void setIndices(std::vector<std::size_t> indices);
    void setTextures(std::vector<Texture> textures);
    void setTextures(std::unordered_map<Texture::TextureType, Texture> textures);
    void setTexture(Texture texture);
};
