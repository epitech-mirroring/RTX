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
#include "primitives/Properties/RectangleProperties.hpp"

class Rectangle : public Object {
    public:
        Rectangle();
        Rectangle(const Material& material, const Transform& transform, const std::vector<Texture>& textures, float length, float width, float height);
        Rectangle(const Material& material, const Transform& transform, const std::vector<Texture>& textures, const RectangleProperties & properties);
        Rectangle(const Rectangle &other);
        explicit Rectangle(JsonObject *obj);
        explicit Rectangle(RectangleProperties &properties);
        ~Rectangle() override = default;

        [[nodiscard]] RectangleProperties getProperties() const;
        [[nodiscard]] RectangleProperties &getProperties();
        float getLength() const { return _properties.getLength(); }
        float getWidth() const { return _properties.getWidth(); }
        float getHeight() const { return _properties.getHeight(); }
        void setLength(float length) { _properties.setLength(length); }
        void setWidth(float width) { _properties.setWidth(width); }
        void setHeight(float height) { _properties.setHeight(height); }

        static std::vector<glm::vec3> generateVertices(const RectangleProperties &properties);
        static std::vector<unsigned int> generateIndices();
    protected:
        RectangleProperties _properties{};
};
