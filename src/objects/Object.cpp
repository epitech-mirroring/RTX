/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Object.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Object::Object()
{
    _material = Material();
    _transform = Transform();
    _vao = 0;
    _vbo = 0;
    _ebo = 0;
}

Object::~Object()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}

Object::Object(const Material& material, const Transform &transform, const std::vector<float> &vertices, const std::vector<std::size_t> &indices, const std::vector<Texture> &textures)
{
    _material = material;
    _transform = transform;
    _vao = 0;
    _vbo = 0;
    _ebo = 0;

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long>(vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Object::Object(const Object &other)
{
    _material = other._material;
    _transform = other._transform;
    _vao = other._vao;
    _vbo = other._vbo;
    _ebo = other._ebo;
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

void Object::setMaterial(const Material &material)
{
    _material = material;
}

void Object::setTransform(const Transform &transform)
{
    _transform = transform;
}

unsigned int Object::getVao() const
{
    return _vao;
}
