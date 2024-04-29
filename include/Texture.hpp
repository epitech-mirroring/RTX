/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "GLSL/Color.hpp"
#include "Material.hpp"

class Texture {
public:
    enum TextureType {
        DIFFUSE,
        SPECULAR,
        NORMAL,
        HEIGHT,
    };
    Texture();
    Texture(const Texture &texture);
    Texture(const std::string &path, const TextureType type);
    ~Texture() = default;
    void setPath(const std::string &path);
    void setType(const TextureType type);
    const std::string &getPath() const;
    const TextureType &getType() const;
private:
    std::string _path;
    TextureType _type;
};
