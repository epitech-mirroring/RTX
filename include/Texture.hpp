/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "json/Json.hpp"
#include <string>
#include "GlmParser.hpp"

class Texture {
public:
    enum TextureType {
        DIFFUSE,
        SPECULAR,
        NORMAL,
        HEIGHT,
        TEXTURE
    };
private:
    std::string _path;
    TextureType _type;
public:
    Texture();
    Texture(const Texture &texture);
    Texture(const std::string &path, TextureType type);
    explicit Texture(JsonObject *obj);
    ~Texture() = default;
    void setPath(const std::string &path);
    void setType(TextureType type);
    [[nodiscard]] std::string getPath() const;
    [[nodiscard]] std::string &getPath();
    [[nodiscard]] TextureType getType() const;
    [[nodiscard]] TextureType &getType();
};
