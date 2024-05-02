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
    _faceCount = 0;
}

Object::~Object()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}

Object::Object(const Material& material, const Transform &transform, const std::vector<glm::vec3> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture> &textures)
{
    _material = material;
    _transform = transform;
    _vao = 0;
    _vbo = 0;
    _ebo = 0;
    if (indices.empty())
        _faceCount = vertices.size() / 3;
    else
        _faceCount = indices.size();

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    auto *verticesArray = new float[vertices.size() * 3];
    for (std::size_t i = 0; i < vertices.size() * 3; i += 3) {
        glm::vec3 vertex = vertices[i / 3];
        verticesArray[i] = vertex.x;
        verticesArray[i + 1] = vertex.y;
        verticesArray[i + 2] = vertex.z;
    }

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, (long) (vertices.size() * 3 * sizeof(float)), verticesArray, GL_STATIC_DRAW);
    delete[] verticesArray;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)nullptr);
    glEnableVertexAttribArray(0);

    if (!indices.empty()) {
        glGenBuffers(1, &_ebo);

        auto *indicesArray = new unsigned int[indices.size()];
        for (std::size_t i = 0; i < indices.size(); i++)
            indicesArray[i] = indices[i];

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long) (indices.size() * sizeof(unsigned int)), indicesArray, GL_STATIC_DRAW);
        delete[] indicesArray;
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Object::Object(const Object &other)
{
    _material = other._material;
    _transform = other._transform;
    _faceCount = other._faceCount;
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

void Object::bind() const
{
    glBindVertexArray(_vao);
}

void Object::unbind() const
{
    glBindVertexArray(0);
}

void Object::draw() const
{
    this->bind();
    if (_ebo != 0)
        glDrawElements(GL_TRIANGLES, (int) _faceCount, GL_UNSIGNED_INT, nullptr);
    else
        glDrawArrays(GL_TRIANGLES, 0, (int) _faceCount);
    this->unbind();
}

void Object::draw(const GLSL::Shader &vertexShader, const GLSL::Shader &fragmentShader, std::function<void(const GLSL::Shader &vertexShader, const GLSL::Shader &fragmentShader)> uniforms) const
{
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader.getShader());
    glAttachShader(shaderProgram, fragmentShader.getShader());
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    if (uniforms)
        uniforms(vertexShader, fragmentShader);
    this->draw();
    glDeleteProgram(shaderProgram);
}
