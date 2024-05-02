/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Object.hpp"
#include "primitives/Properties/cubeProperties.hpp"
#include "json/Json.hpp"

class Cube : public Object {
    public:
        Cube();
        Cube(const Material& material, const Transform& transform, std::vector<glm::vec3> vertices, std::vector<std::size_t> indices, std::vector<Texture> textures, std::size_t size);
        Cube(const Material& material, const Transform& transform, std::vector<glm::vec3> vertices, std::vector<std::size_t> indices, std::vector<Texture> textures, cubeProperties properties);
        Cube(const Cube &other);
        explicit Cube(JsonObject *obj);
        ~Cube() = default;

        [[nodiscard]] abstractProperties getProperties() const;
        [[nodiscard]] cubeProperties &getProperties();
    protected:
        cubeProperties _properties{};
};
