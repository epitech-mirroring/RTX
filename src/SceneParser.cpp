/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "SceneParser.hpp"
#include "json/Json.hpp"
#include <iostream>
#include <fstream>

SceneParser::SceneParser()
{
    _Scene = Scene();
}

SceneParser::SceneParser(std::string &path)
{
    _Scene = Scene();
    if (path.substr(path.find_last_of(".") + 1) != "json") {
        std::cerr << "Error: Invalid file format, need .json and get " +  path.find_last_of(".") << std::endl;
        path = "";
        return;
    }
    this->_path = path;
}

void SceneParser::setPath(std::string &path)
{
    if (path.substr(path.find_last_of(".") + 1) != "json") {
        throw std::invalid_argument("Error: Invalid file format, need .json and get " +  path.find_last_of("."));
        path = "";
        return;
    }
    this->_path = path;
}

void SceneParser::parse()
{
    std::ifstream file(this->_path);

    if (!file.is_open()) {
        throw std::invalid_argument("Error: can't open Scene file");
        return;
    }
    file.close();
    JsonObject root = JsonObject::parseFile(this->_path);
}

Scene &SceneParser::getScene()
{
    return _Scene;
}

Scene SceneParser::getScene() const
{
    return _Scene;
}

GLSL::Color SceneParser::parseColor(JsonObject *obj)
{
    GLSL::Color color;

    color.setR(obj->getInt("r"));
    color.setG(obj->getInt("g"));
    color.setB(obj->getInt("b"));
    color.setA(obj->getInt("a"));
    return color;
}

GLSL::Quaternion SceneParser::parseQuaternion(JsonObject *obj)
{
    GLSL::Quaternion quaternion;

    quaternion.x = obj->getInt("x");
    quaternion.y = obj->getInt("y");
    quaternion.z = obj->getInt("z");
    quaternion.w = obj->getInt("w");
    return quaternion;
}

GLSL::Vector<3> SceneParser::parseVector(JsonObject *obj)
{
    GLSL::Vector<3> vector;
    std::string key;

    for (std::size_t i = 0; i < 3; i++) {
        if (i == 0)
            key = "x";
        if (i == 1)
            key = "y";
        if (i == 2)
            key = "z";
        vector[i] = obj->getInt(key);
    }
    return vector;
}

Camera SceneParser::parseCamera(JsonObject *obj)
{
    Camera camera;
    JsonObject *transform = obj->getValue<JsonObject>("transform");

    camera.setTransform(this->parseTransform(transform));
    camera.setFov(obj->getInt("fov"));
    camera.setAspect(obj->getInt("aspect"));
    camera.setNear(obj->getInt("near"));
    return camera;
}

Material SceneParser::parseMaterial(JsonObject *obj)
{
    Material material;

    material.setColor(this->parseColor(obj->getValue<JsonObject>("color")));
    material.setEmission(this->parseColor(obj->getValue<JsonObject>("emission")));
    material.setBrightness(obj->getInt("brightness"));
    material.setRoughness(obj->getInt("rougghness"));
    return material;
}

Texture SceneParser::parseTexture(JsonObject *obj)
{
    Texture texture;

    texture.setPath(obj->getString("path"));
    std::string type = obj->getString("type");
    if (type == "diffuse")
        texture.setType(Texture::TextureType::DIFFUSE);
    else if (type == "specular")
        texture.setType(Texture::TextureType::SPECULAR);
    else if (type == "normal")
        texture.setType(Texture::TextureType::NORMAL);
    else if (type == "height")
        texture.setType(Texture::TextureType::HEIGHT);
    else {
        throw std::invalid_argument("Error: Invalid texture type");
        return texture;
    }
    return texture;
}

Transform SceneParser::parseTransform(JsonObject *obj)
{
    Transform transform;

    transform.setPosition(this->parseVector(obj->getValue<JsonObject>("position")));
    transform.setRotation(this->parseQuaternion(obj->getValue<JsonObject>("rotation")));
    transform.setScale(this->parseVector(obj->getValue<JsonObject>("scale")));
    return transform;
}

Object SceneParser::parseObject(JsonObject *obj)
{
    Object object;

    object.setTransform(this->parseTransform(obj->getValue<JsonObject>("transform")));
    object.setMaterial(this->parseMaterial(obj->getValue<JsonObject>("material")));
    object.setTexture(this->parseTexture(obj->getValue<JsonObject>("texture")));
    return object;
}
