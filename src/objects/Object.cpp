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
    _properties = AbstractProperties();
}

Object::Object(const Material& material, const Transform& transform, const std::vector<glm::vec3> &vertices, const std::vector<unsigned  int> &indices, const std::vector<Texture>& textures)
{
    _properties = AbstractProperties();
    _properties.setMaterial(material);
    _properties.setTransform(transform);
    _properties.setTextures(textures);
    _vertices = vertices;
    _indices = indices;
}

Object::Object(const Object &other)
{
    _properties = other._properties;
}

Object::Object(JsonObject *obj)
{
    _properties = AbstractProperties();
}

Object::Object(AbstractProperties &properties)
{
    _properties = properties;
}

Material Object::getMaterial() const
{
    return _properties.getMaterial();
}

Material &Object::getMaterial()
{
    return _properties.getMaterial();
}

Transform Object::getTransform() const
{
    return _properties.getTransform();
}

Transform &Object::getTransform()
{
    return _properties.getTransform();
}

std::vector<glm::vec3> &Object::getVertices()
{
    return _vertices;
}

std::vector<glm::vec3> Object::getVertices() const
{
    return _vertices;
}

std::vector<unsigned int> &Object::getIndices()
{
    return _indices;
}

std::vector<unsigned int> Object::getIndices() const
{
    return _indices;
}

std::unordered_map<Texture::TextureType, Texture> &Object::getTextures()
{
    return _properties.getTextures();
}

std::unordered_map<Texture::TextureType, Texture> Object::getTextures() const
{
    return _properties.getTextures();
}

Texture Object::getTexture(Texture::TextureType type) const
{
    return _properties.getTextures().at(type);
}

Texture &Object::getTexture(Texture::TextureType type)
{
    return _properties.getTextures().at(type);
}

void Object::setMaterial(const Material& material)
{
    _properties.setMaterial(material);
}

void Object::setTransform(const Transform& transform)
{
    _properties.setTransform(transform);
}

void Object::setVertices(std::vector<glm::vec3> vertices)
{
    _vertices = std::move(vertices);
}

void Object::setIndices(std::vector<unsigned int> indices)
{
    _indices = std::move(indices);
}

void Object::setTextures(std::vector<Texture> textures)
{
    _properties.setTextures(std::move(textures));
}

void Object::setTextures(std::unordered_map<Texture::TextureType, Texture> textures)
{
    _properties.setTextures(std::move(textures));
}

void Object::setTexture(Texture texture)
{
    _properties.setTextures({{texture.getType(), texture}});
}

void Object::setProperties(const AbstractProperties& properties)
{
    _properties = properties;
}
