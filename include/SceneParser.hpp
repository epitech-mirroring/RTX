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
#include "primitives/ObjectsFactory.hpp"
#include "primitives/Properties/PropertiesFactory.hpp"
#include "../parser/obj/include/obj/ObjParser.hpp"

class SceneParser {
    public:
        SceneParser();
        explicit SceneParser(std::string &path, PropertiesFactory &propertiesFactory, ObjectsFactory &objectsFactory);
        ~SceneParser() = default;
        void setPath(std::string &path, std::vector<std::string> &previousPaths);
        void parse();
        [[nodiscard]] Scene &getScene();
        [[nodiscard]] Scene getScene() const;
        static std::vector<Camera> parseCameras(JsonObject &obj);
        std::vector<Object *> parseObjects(JsonObject &obj);
        void parseSceneSettings(JsonObject *obj);
    private:
        std::string _path;
        Scene _scene;
        ObjectsFactory _objectsFactory;
        PropertiesFactory _propertiesFactory;
        ObjParser _objParser;
};
