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

struct Triangle {
    alignas(16) glm::vec3 v0;
    alignas(16) glm::vec3 v1;
    alignas(16) glm::vec3 v2;
    alignas(16) glm::vec3 normalV0;
    alignas(16) glm::vec3 normalV1;
    alignas(16) glm::vec3 normalV2;
    alignas(8) glm::vec2 uv0;
    alignas(8) glm::vec2 uv1;
    alignas(8) glm::vec2 uv2;
};

struct RaytracingMaterial {
    alignas(16) glm::vec3 color;
    alignas(16) glm::vec3 emission;
    alignas(4) float emissionIntensity;
    alignas(4) float roughness;
    alignas(4) float transparency;
    alignas(4) float refractionIndex;
    alignas(4) bool hasCheckerPattern;
};

struct Mesh {
    alignas(4) unsigned int startIdx;
    alignas(4) unsigned int endIdx;
    alignas(16) glm::vec3 boundingBoxMin;
    alignas(16) glm::vec3 boundingBoxMax;
    alignas(16) glm::mat4 transform;
    alignas(4) float textureOffset;
    alignas(8) glm::vec2 textureSize;
    RaytracingMaterial material;
};

class Object {
protected:
    AbstractProperties _properties;
    std::vector<Triangle> _triangles;
public:
    Object();
    Object(const Material& material, const Transform& transform, const std::vector<Triangle> &triangles, const std::vector<Texture>& textures);
    Object(const Object &other);
    explicit Object(JsonObject *obj);
    explicit Object(AbstractProperties &properties);
    virtual ~Object() = default;

    Transform &getTransform();
    [[nodiscard]] Transform getTransform() const;
    Material &getMaterial();
    Material getMaterial() const;
    std::vector<Triangle> &getTriangles();
    std::vector<Triangle> getTriangles() const;
    std::unordered_map<Texture::TextureType, Texture> &getTextures();
    std::unordered_map<Texture::TextureType, Texture> getTextures() const;
    Texture &getTexture(Texture::TextureType type);
    Texture getTexture(Texture::TextureType type) const;

    void setTransform(const Transform& transform);
    void setMaterial(const Material& material);
    void setTriangles(std::vector<Triangle> triangles);
    void setTextures(std::vector<Texture> textures);
    void setTextures(std::unordered_map<Texture::TextureType, Texture> textures);
    void setTexture(Texture texture);
    void setProperties(const AbstractProperties& properties);
};
