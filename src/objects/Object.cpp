
/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Object.hpp"
#include <GLFW/glfw3.h>
#include <utility>

Object::Object()
{
    _properties = AbstractProperties();
}

Object::Object(const Material& material, const Transform& transform, const std::vector<Triangle> &triangles, const std::vector<Texture>& textures)
{
    _properties = AbstractProperties();
    _properties.setMaterial(material);
    _properties.setTransform(transform);
    _properties.setTextures(textures);
    _triangles = triangles;
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

std::vector<Triangle> Object::getTriangles() const
{
    return _triangles;
}

std::vector<Triangle> &Object::getTriangles()
{
    return _triangles;
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

void Object::setTriangles(std::vector<Triangle> triangles)
{
    _triangles = std::move(triangles);
}

void Object::setProperties(const AbstractProperties& properties)
{
    _properties = properties;
}
