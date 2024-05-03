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
        Rectangle(const Material& material, const Transform& transform, const std::vector<Texture>& textures, std::size_t length, std::size_t width, std::size_t height);
        Rectangle(const Material& material, const Transform& transform, const std::vector<Texture>& textures, const RectangleProperties & properties);
        Rectangle(const Rectangle &other);
        explicit Rectangle(JsonObject *obj);
        explicit Rectangle(RectangleProperties &properties);
        ~Rectangle() override = default;

        [[nodiscard]] RectangleProperties getProperties() const;
        [[nodiscard]] RectangleProperties &getProperties();
        std::size_t getLength() const { return _properties.getLength(); }
        std::size_t getWidth() const { return _properties.getWidth(); }
        std::size_t getHeight() const { return _properties.getHeight(); }
        void setLength(std::size_t length) { _properties.setLength(length); }
        void setWidth(std::size_t width) { _properties.setWidth(width); }
        void setHeight(std::size_t height) { _properties.setHeight(height); }

        static std::vector<glm::vec3> generateVertices(const RectangleProperties &properties);
        static std::vector<unsigned int> generateIndices();
    protected:
        RectangleProperties _properties{};
};
