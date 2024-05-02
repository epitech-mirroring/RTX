/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Properties/AbstractProperties.hpp"

#include <utility>

AbstractProperties::AbstractProperties()
{
    _material = Material();
    _transform = Transform();
    _vertices = std::vector<glm::vec3>();
    _indices = std::vector<std::size_t>();
    _textures = std::unordered_map<Texture::TextureType, Texture>();
}

Material &AbstractProperties::getMaterial()
{
    return _material;
}

Material AbstractProperties::getMaterial() const
{
    return _material;
}

Transform &AbstractProperties::getTransform()
{
    return _transform;
}

Transform AbstractProperties::getTransform() const
{
    return _transform;
}

std::vector<glm::vec3> &AbstractProperties::getVertices()
{
    return _vertices;
}

std::vector<glm::vec3> AbstractProperties::getVertices() const
{
    return _vertices;
}

std::vector<std::size_t> &AbstractProperties::getIndices()
{
    return _indices;
}

std::vector<std::size_t> AbstractProperties::getIndices() const
{
    return _indices;
}

std::unordered_map<Texture::TextureType, Texture> &AbstractProperties::getTextures()
{
    return _textures;
}

std::unordered_map<Texture::TextureType, Texture> AbstractProperties::getTextures() const
{
    return _textures;
}

Texture &AbstractProperties::getTexture(Texture::TextureType type)
{
    return _textures[type];
}

Texture AbstractProperties::getTexture(Texture::TextureType type) const
{
    return _textures.at(type);
}

void AbstractProperties::setMaterial(const Material &material)
{
    _material = material;
}

void AbstractProperties::setTransform(const Transform &transform)
{
    _transform = transform;
}

void AbstractProperties::setVertices(std::vector<glm::vec3> vertices)
{
    _vertices = std::move(vertices);
}

void AbstractProperties::setIndices(std::vector<std::size_t> indices)
{
    _indices = std::move(indices);
}

void AbstractProperties::setTextures(std::vector<Texture> textures)
{
    for (auto &texture : textures) {
        _textures[texture.getType()] = texture;
    }
}

void AbstractProperties::setTextures(std::unordered_map<Texture::TextureType, Texture> textures)
{
    _textures = std::move(textures);
}

void AbstractProperties::setTexture(Texture texture)
{
    _textures[texture.getType()] = texture;
}

AbstractProperties::AbstractProperties(const Material &material, const Transform &transform, std::vector<glm::vec3> vertices, std::vector<std::size_t> indices, std::unordered_map<Texture::TextureType, Texture> textures)
{
    _material = material;
    _transform = transform;
    _vertices = std::move(vertices);
    _indices = std::move(indices);
    _textures = std::move(textures);
}

AbstractProperties::AbstractProperties(const AbstractProperties &other)
{
    _material = other.getMaterial();
    _transform = other.getTransform();
    _vertices = other.getVertices();
    _indices = other.getIndices();
    _textures = other.getTextures();
}

AbstractProperties::AbstractProperties(JsonObject *obj)
{
    _material = Material(obj->getValue<JsonObject>("material"));
    _transform = Transform(obj->getValue<JsonObject>("transform"));
    auto textures = obj->getValue<JsonArray>("textures");
    for (std::size_t i = 0; i < textures->size(); i++) {
        auto texture = Texture(textures->getValue<JsonObject>(i));
        _textures[texture.getType()] = texture;
    }
}
