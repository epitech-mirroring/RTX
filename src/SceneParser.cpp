/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "SceneParser.hpp"
#include <iostream>
#include <fstream>

SceneParser::SceneParser()
{
    _scene = Scene();
    _propertiesFactory = PropertiesFactory();
    _objectsFactory = ObjectsFactory();
    _objParser = ObjParser();
}

SceneParser::SceneParser(std::string &path, PropertiesFactory &propertiesFactory, ObjectsFactory &objectsFactory)
{
    _scene = Scene();
    _propertiesFactory = propertiesFactory;
    _objectsFactory = objectsFactory;
    _objParser = ObjParser();
    if (path.substr(path.find_last_of('.') + 1) != "json") {
        std::cerr << &"Error: Invalid file format, need .json and get " [  path.find_last_of(".")] << std::endl;
        path = "";
        return;
    }
    this->_path = path;
}

void SceneParser::setPath(std::string &path)
{
    if (path.substr(path.find_last_of('.') + 1) != "json") {
        path = "";
        throw std::invalid_argument(&"Error: Invalid file format, need .json and get " [  path.find_last_of('.')]);
    }
    this->_path = path;
}

void SceneParser::parse()
{
    std::ifstream file(this->_path);

    if (!file.is_open()) {
        throw std::invalid_argument("Error: can't open Scene file");
    }
    file.close();
    JsonObject root = JsonObject::parseFile(this->_path);
    this->_scene.setCameras(SceneParser::parseCameras(root));
    this->_scene.setObjects(this->parseObjects(root));
    this->parseSceneSettings(root.getValue<JsonObject>("settings"));
}

std::vector<Camera> SceneParser::parseCameras(JsonObject &root)
{
    JsonArray *cameras;
    std::vector<Camera> camerasVector;

    try {
        cameras = root.getValue<JsonArray>("cameras");
    } catch (std::exception &e) {
        throw std::invalid_argument("Error: No cameras array in Scene file");
    }
    if (cameras->size() == 0) {
        throw std::invalid_argument("Error: Empty cameras array in Scene file");
    }
    for (std::size_t i = 0; i < cameras->size() ; i++) {
        auto *cameraJson = cameras->getValue<JsonObject>(i);
        auto camera = Camera(cameraJson);
        camerasVector.push_back(camera);
    }
    return camerasVector;
}

std::vector<Object *> SceneParser::parseObjects(JsonObject &root)
{
    JsonArray *objects;
    std::vector<Object *> objectsVector;
    Object *object;

    try {
        objects = root.getValue<JsonArray>("objects");
    } catch (std::exception &e) {
        throw std::invalid_argument("Error: No objects array in Scene file");
    }
    if (objects->size() == 0) {
        throw std::invalid_argument("Error: Empty objects array in Scene file");
    }
    for (std::size_t i = 0; i < objects->size() ; i++) {
        auto *objectJson = objects->getValue<JsonObject>(i);
        if (objectJson->getString("type") == "obj") {
            object = _objParser.parseFile(objectJson->getString("path"));
            object->setTransform(Transform(objectJson->getValue<JsonObject>("transform")));
        } else {
            object = _objectsFactory.createObject(objectJson->getString("type"), *_propertiesFactory.createProperties(objectJson->getString("type"), objectJson));
        }
        objectsVector.push_back(object);
    }
    return objectsVector;
}

void SceneParser::parseSceneSettings(JsonObject *obj)
{
    if (obj == nullptr) {
        return;
    }
    try {
        _scene.setSkyBoxEnabled(obj->getBoolean("skybox-enabled"));
    } catch (std::exception &e) {
        _scene.setSkyBoxEnabled(false);
    }
}

Scene &SceneParser::getScene()
{
    return _scene;
}

Scene SceneParser::getScene() const
{
    return _scene;
}
