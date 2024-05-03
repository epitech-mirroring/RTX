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
        AbstractProperties(const Material &material, const Transform &transform, std::unordered_map<Texture::TextureType, Texture> textures);
        AbstractProperties(const AbstractProperties &other);
        explicit AbstractProperties(JsonObject *obj);
        virtual ~AbstractProperties() = default;

        Transform &getTransform();
        Transform getTransform() const;
        Material &getMaterial();
        Material getMaterial() const;
        std::unordered_map<Texture::TextureType, Texture> &getTextures();
        std::unordered_map<Texture::TextureType, Texture> getTextures() const;
        Texture &getTexture(Texture::TextureType type);
        Texture getTexture(Texture::TextureType type) const;

        void setTransform(const Transform& transform);
        void setMaterial(const Material& material);
        void setTextures(std::vector<Texture> textures);
        void setTextures(std::unordered_map<Texture::TextureType, Texture> textures);
        void setTexture(Texture texture);
    private:
        Material _material;
        Transform _transform;
        std::unordered_map<Texture::TextureType, Texture> _textures;
};
