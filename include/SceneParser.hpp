/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Scene.hpp"
#include "json/Json.hpp"

class SceneParser {
    public:
        SceneParser();
        SceneParser(std::string &path);
        ~SceneParser() = default;
        void setPath(std::string &path);
        void parse();
        [[nodiscard]] Scene &getScene();
        [[nodiscard]] Scene getScene() const;

        GLSL::Color parseColor(JsonObject *obj);
        GLSL::Quaternion parseQuaternion(JsonObject *obj);
        GLSL::Vector<3> parseVector(JsonObject *obj);
        Material parseMaterial(JsonObject *obj);
        Texture parseTexture(JsonObject *obj);
        Transform parseTransform(JsonObject *obj);
        Camera parseCamera(JsonObject *obj);
        Object parseObject(JsonObject *obj);
    private:
        std::string _path;
        Scene _Scene;

};
