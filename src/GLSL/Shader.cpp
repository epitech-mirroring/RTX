/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "GLSL/Shader.hpp"
#include <fstream>
#include <GLFW/glfw3.h>

using namespace GLSL;

static int shaderTypeToGLSLType(Shader::Type type) {
    /*switch (type) {
        case Shader::Type::VERTEX:
            return GL_VERTEX_SHADER;
        case Shader::Type::FRAGMENT:
            return GL_FRAGMENT_SHADER;
        case Shader::Type::COMPUTE:
            return GL_COMPUTE_SHADER;
        default:
            throw std::runtime_error("Error: Invalid shader type");
    }*/
}

Shader::Shader(Shader::Type type, const std::string &path) {
    _type = type;
    _id = 0;
    _shader = 0;
    /*// Load the fragment shader
    std::ifstream shaderFile(path);
    if (!shaderFile.is_open()) {
        throw std::runtime_error("Error: Failed to open shader file");
    }

    std::string shaderSource(
            (std::istreambuf_iterator<char>(shaderFile)),
            std::istreambuf_iterator<char>());
    shaderFile.close();

    // Compile shader
    _shader = glCreateShader(shaderTypeToGLSLType(type));
    const char *shaderSourceCStr = shaderSource.c_str();
    glShaderSource(_shader, 1, &shaderSourceCStr, nullptr);
    glCompileShader(_shader);
    int success;
    char infoLog[512];
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_shader, 512, nullptr, infoLog);
        throw std::runtime_error("Error: Failed to compile shader\n" + std::string(infoLog));
    }

    // Load shader program
    _id = glCreateProgram();
    glAttachShader(_id, _shader);
    glLinkProgram(_id);
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_id, 512, nullptr, infoLog);
        throw std::runtime_error("Error: Failed to link shader program\n" + std::string(infoLog));
    }*/
}

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
    Shader vertex(Shader::Type::VERTEX, vertexPath);
    Shader fragment(Shader::Type::FRAGMENT, fragmentPath);

    _type = Shader::Type::VERTEX_FRAGMENT;
    _id = 0;
    _shader = 0;
    /*glAttachShader(_id, vertex.getShader());
    glAttachShader(_id, fragment.getShader());
    glLinkProgram(_id);
    int success;
    char infoLog[512];
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_id, 512, nullptr, infoLog);
        throw std::runtime_error("Error: Failed to link shader program\n" + std::string(infoLog));
    }*/
}

Shader::~Shader() {
    /*if (_type != Shader::Type::VERTEX_FRAGMENT)
        glDeleteShader(_shader);
    glDeleteProgram(_id);*/
}

unsigned int Shader::getId() const {
    return _id;
}

Shader::Type Shader::getType() const {
    return _type;
}

unsigned int Shader::getShader() const {
    return _shader;
}

void Shader::use() const {
    //glUseProgram(_id);
}

void Shader::setBool(const std::string &name, bool value) const {
    //glUniform1i(glGetUniformLocation(_id, name.c_str()), (int) value);
}

void Shader::setInt(const std::string &name, int value) const {
    //glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    //glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
    /*const float data[2] = {(float) value[0], (float) value[1]};
    int location = glGetUniformLocation(_id, name.c_str());
    glUniform2fv(location, 1, data);*/
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    /*const float data[3] = {(float) value[0], (float) value[1], (float) value[2]};
    glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, data);*/
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    /*const float data[4] = {(float) value[0], (float) value[1], (float) value[2], (float) value[3]};
    glUniform4fv(glGetUniformLocation(_id, name.c_str()), 1, data);*/
}

void Shader::setMat2(const std::string &name, const glm::mat2 &value) const {
    /*const float data[4] = {(float) value[0][0], (float) value[0][1], (float) value[1][0], (float) value[1][1]};
    glUniformMatrix2fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, data);*/
}

void Shader::setMat3(const std::string &name, const glm::mat3 &value) const {
    /*const float data[9] = {
            (float) value[0][0], (float) value[0][1], (float) value[0][2],
            (float) value[1][0], (float) value[1][1], (float) value[1][2],
            (float) value[2][0], (float) value[2][1], (float) value[2][2]
    };
    glUniformMatrix3fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, data);*/
}

void Shader::setMat4(const std::string &name, const glm::mat4 &value) const {
    /*const float data[16] = {
            (float) value[0][0], (float) value[0][1], (float) value[0][2], (float) value[0][3],
            (float) value[1][0], (float) value[1][1], (float) value[1][2], (float) value[1][3],
            (float) value[2][0], (float) value[2][1], (float) value[2][2], (float) value[2][3],
            (float) value[3][0], (float) value[3][1], (float) value[3][2], (float) value[3][3]
    };
    glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, data);*/
}

void Shader::setUInt(const std::string &name, unsigned int value) const {
    //glUniform1ui(glGetUniformLocation(_id, name.c_str()), value);
}
