/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Object.hpp"
#include "json/Json.hpp"
#include "primitives/Properties/CubeProperties.hpp"

class Cube : public Object {
    public:
        Cube();
        Cube(const Material& material, const Transform& transform, const std::vector<glm::vec3>& vertices, const std::vector<std::size_t>& indices, const std::vector<Texture>& textures, std::size_t size);
        Cube(const Material& material, const Transform& transform, const std::vector<glm::vec3>& vertices, const std::vector<std::size_t>& indices, const std::vector<Texture>& textures, const CubeProperties& properties);
        Cube(const Cube &other);
        explicit Cube(JsonObject *obj);
        explicit Cube(CubeProperties &properties);
        ~Cube() = default;

        [[nodiscard]] CubeProperties getProperties() const;
        [[nodiscard]] CubeProperties &getProperties();
        std::size_t getSize() const { return _properties.getSize(); }
        std::size_t &getSize() { return _properties.getSize(); }
    protected:
        CubeProperties _properties{};
};
