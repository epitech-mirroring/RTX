/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <iostream>
#include <string>
#include <glm/glm.hpp>

namespace GLSL {
    class Shader {
    public:
        enum class Type {
            VERTEX,
            FRAGMENT,
            COMPUTE,
            VERTEX_FRAGMENT
        };
    protected:
        Shader::Type _type;
        unsigned int _id;
        unsigned int _shader;
    public:
        Shader(Shader::Type type, const std::string &path);
        Shader(const std::string &vertexPath, const std::string &fragmentPath);
        ~Shader();

        [[nodiscard]] unsigned int getId() const;
        [[nodiscard]] unsigned int getShader() const;
        [[nodiscard]] Shader::Type getType() const;
        void use() const;

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setUInt(const std::string &name, unsigned int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec2(const std::string &name, const glm::vec2 &value) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec4(const std::string &name, const glm::vec4 &value) const;
        void setMat2(const std::string &name, const glm::mat2 &value) const;
        void setMat3(const std::string &name, const glm::mat3 &value) const;
        void setMat4(const std::string &name, const glm::mat4 &value) const;
    };
}
