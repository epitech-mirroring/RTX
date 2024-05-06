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
#include "primitives/Properties/SphereProperties.hpp"

class Sphere : public Object {
    public:
        Sphere();
        Sphere(const Material& material, const Transform& transform, const std::vector<Texture>& textures, std::size_t radius);
        Sphere(const Material& material, const Transform& transform, const std::vector<Texture>& textures, const SphereProperties& properties);
        Sphere(const Sphere &other);
        explicit Sphere(JsonObject *obj);
        explicit Sphere(SphereProperties &properties);
        ~Sphere() override = default;
        [[nodiscard]] SphereProperties getProperties() const;
        [[nodiscard]] SphereProperties &getProperties();

        static std::vector<Triangle> generateVertices(const SphereProperties &properties);
        static std::vector<Triangle> duplicateTriangles(std::vector<Triangle>& vertex);
    protected:
        SphereProperties _properties;
        void setProperties(const SphereProperties &properties);
};
