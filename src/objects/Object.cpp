/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Object.hpp"

Object::Object()
{
    _material = Material();
    _transform = Transform();
    _vertices = std::vector<GLSL::Vertex>();
    _indices = std::vector<std::size_t>();
    _textures = std::unordered_map<Texture::TextureType, Texture>();
}

Object::Object(Material material, Transform transform, std::vector<GLSL::Vertex> vertices, std::vector<std::size_t> indices, std::vector<Texture> textures)
{
    _material = material;
    _transform = transform;
    _vertices = vertices;
    _indices = indices;
    for (auto &texture : textures)
        _textures[texture.getType()] = texture;
}

Object::Object(const Object &other)
{
    _material = other._material;
    _transform = other._transform;
    _vertices = other._vertices;
    _indices = other._indices;
    _textures = other._textures;
}

Material Object::getMaterial() const
{
    return _material;
}

Material &Object::getMaterial()
{
    return _material;
}

Transform Object::getTransform() const
{
    return _transform;
}

Transform &Object::getTransform()
{
    return _transform;
}

std::vector<GLSL::Vertex> &Object::getVertices()
{
    return _vertices;
}

std::vector<GLSL::Vertex> Object::getVertices() const
{
    return _vertices;
}

std::vector<std::size_t> &Object::getIndices()
{
    return _indices;
}

std::vector<std::size_t> Object::getIndices() const
{
    return _indices;
}

std::vector<Texture> &Object::getTextures()
{
    std::vector<Texture> textures;
    for (auto &texture : _textures)
        textures.push_back(texture.second);
    return textures;
}

std::vector<Texture> Object::getTextures() const
{
    std::vector<Texture> textures;
    for (auto &texture : _textures)
        textures.push_back(texture.second);
    return textures;
}

Texture Object::getTexture(Texture::TextureType type) const
{
    return _textures.at(type);
}

Texture &Object::getTexture(Texture::TextureType type)
{
    return _textures.at(type);
}

void Object::setMaterial(Material material)
{
    _material = material;
}

void Object::setTransform(Transform transform)
{
    _transform = transform;
}

void Object::setVertices(std::vector<GLSL::Vertex> vertices)
{
    _vertices = vertices;
}

void Object::setIndices(std::vector<std::size_t> indices)
{
    _indices = indices;
}

void Object::setTextures(std::vector<Texture> textures)
{
    for (auto &texture : textures)
        _textures[texture.getType()] = texture;
}

void Object::setTextures(std::unordered_map<Texture::TextureType, Texture> textures)
{
    _textures = textures;
}

void Object::setTexture(Texture texture)
{
    _textures[texture.getType()] = texture;
}
