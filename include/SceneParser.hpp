/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Scene.hpp"
#include "primitives/objectsFactory.hpp"
#include "json/Json.hpp"

class SceneParser {
    public:
        SceneParser();
        explicit SceneParser(std::string &path);
        ~SceneParser() = default;
        void setPath(std::string &path);
        void parse();
        [[nodiscard]] Scene &getScene();
        [[nodiscard]] Scene getScene() const;
        static std::vector<Camera> parseCameras(JsonObject &obj);
        static std::vector<Object> parseObjects(JsonObject &obj);
    private:
        std::string _path;
        Scene _scene;

};
