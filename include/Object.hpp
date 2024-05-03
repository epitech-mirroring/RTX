/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <glm/glm.hpp>
#include "json/Json.hpp"
#include "primitives/Properties/AbstractProperties.hpp"

class Object {
protected:
    AbstractProperties _properties;
    std::vector<glm::vec3> _vertices;
    std::vector<unsigned int> _indices;
public:
    Object();
    Object(const Material& material, const Transform& transform, const std::vector<glm::vec3> &vertices, const std::vector<unsigned  int> &indices, const std::vector<Texture>& textures);
    Object(const Object &other);
    explicit Object(JsonObject *obj);
    explicit Object(AbstractProperties &properties);
    virtual ~Object() = default;

    Transform &getTransform();
    [[nodiscard]] Transform getTransform() const;
    Material &getMaterial();
    Material getMaterial() const;
    std::vector<glm::vec3> &getVertices();
    std::vector<glm::vec3> getVertices() const;
    std::vector<unsigned int> &getIndices();
    std::vector<unsigned int> getIndices() const;
    std::unordered_map<Texture::TextureType, Texture> &getTextures();
    std::unordered_map<Texture::TextureType, Texture> getTextures() const;
    Texture &getTexture(Texture::TextureType type);
    Texture getTexture(Texture::TextureType type) const;

    void setTransform(const Transform& transform);
    void setMaterial(const Material& material);
    void setVertices(std::vector<glm::vec3> vertices);
    void setIndices(std::vector<unsigned int> indices);
    void setTextures(std::vector<Texture> textures);
    void setTextures(std::unordered_map<Texture::TextureType, Texture> textures);
    void setTexture(Texture texture);
    void setProperties(const AbstractProperties& properties);
};
