/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <vector>
#include <unordered_map>
#include "Material.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "json/Json.hpp"

class AbstractProperties {
    public:
        AbstractProperties();
        AbstractProperties(const Material &material, const Transform &transform, std::vector<glm::vec3> vertices, std::vector<std::size_t> indices, std::unordered_map<Texture::TextureType, Texture> textures);
        AbstractProperties(const AbstractProperties &other);
        explicit AbstractProperties(JsonObject *obj);
        virtual ~AbstractProperties() = default;

        Transform &getTransform();
        Transform getTransform() const;
        Material &getMaterial();
        Material getMaterial() const;
        std::vector<glm::vec3> &getVertices();
        std::vector<glm::vec3> getVertices() const;
        std::vector<std::size_t> &getIndices();
        std::vector<std::size_t> getIndices() const;
        std::unordered_map<Texture::TextureType, Texture> &getTextures();
        std::unordered_map<Texture::TextureType, Texture> getTextures() const;
        Texture &getTexture(Texture::TextureType type);
        Texture getTexture(Texture::TextureType type) const;

        void setTransform(const Transform& transform);
        void setMaterial(const Material& material);
        void setVertices(std::vector<glm::vec3> vertices);
        void setIndices(std::vector<std::size_t> indices);
        void setTextures(std::vector<Texture> textures);
        void setTextures(std::unordered_map<Texture::TextureType, Texture> textures);
        void setTexture(Texture texture);
    private:
        Material _material;
        Transform _transform;
        std::vector<glm::vec3> _vertices;
        std::vector<std::size_t> _indices;
        std::unordered_map<Texture::TextureType, Texture> _textures;
};
