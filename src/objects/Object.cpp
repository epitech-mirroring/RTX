/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Object.hpp"
#include <utility>

Object::Object()
{
    _material = Material();
    _transform = Transform();
    _vertices = std::vector<GLSL::Vertex>();
    _indices = std::vector<std::size_t>();
    _textures = std::unordered_map<Texture::TextureType, Texture>();
    _properties = abstractProperties();
}

Object::Object(const Material& material, const Transform& transform, std::vector<GLSL::Vertex> vertices, std::vector<std::size_t> indices, std::vector<Texture> textures, abstractProperties properties)
{
    _material = material;
    _transform = transform;
    _vertices = std::move(vertices);
    _indices = std::move(indices);
    _properties = abstractProperties();
    for (auto &texture : textures)
        _textures[texture.getType()] = texture;
    _properties = properties;
}

Object::Object(const Object &other)
{
    _material = other._material;
    _transform = other._transform;
    _vertices = other._vertices;
    _indices = other._indices;
    _textures = other._textures;
    _properties = other._properties;
}

Object::Object(JsonObject *obj)
{
    _material = Material(obj->getValue<JsonObject>("material"));
    _transform = Transform(obj->getValue<JsonObject>("transform"));
    _vertices = std::vector<GLSL::Vertex>();
    _indices = std::vector<std::size_t>();
    auto textures = obj->getValue<JsonArray>("textures");
    for (std::size_t i = 0; i < textures->size(); i++) {
        auto texture = Texture(textures->getValue<JsonObject>(i));
        _textures[texture.getType()] = texture;
    }
    _properties = abstractProperties();
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

std::unordered_map<Texture::TextureType, Texture> &Object::getTextures()
{
    return _textures;
}

std::unordered_map<Texture::TextureType, Texture> Object::getTextures() const
{
    return _textures;
}

Texture Object::getTexture(Texture::TextureType type) const
{
    return _textures.at(type);
}

Texture &Object::getTexture(Texture::TextureType type)
{
    return _textures.at(type);
}

void Object::setMaterial(const Material& material)
{
    _material = material;
}

void Object::setTransform(const Transform& transform)
{
    _transform = transform;
}

void Object::setVertices(std::vector<GLSL::Vertex> vertices)
{
    _vertices = std::move(vertices);
}

void Object::setIndices(std::vector<std::size_t> indices)
{
    _indices = std::move(indices);
}

void Object::setTextures(std::vector<Texture> textures)
{
    for (auto &texture : textures)
        _textures[texture.getType()] = texture;
}

void Object::setTextures(std::unordered_map<Texture::TextureType, Texture> textures)
{
    _textures = std::move(textures);
}

void Object::setTexture(Texture texture)
{
    _textures[texture.getType()] = texture;
}

void Object::setProperties(abstractProperties properties)
{
    _properties = properties;
}
