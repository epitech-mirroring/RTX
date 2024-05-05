/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Scene.hpp"
#include <utility>

Scene::Scene()
{
    _objects = std::vector<Object *>();
    _cameras = std::vector<Camera>();
}

Scene::Scene(Scene const &other)
{
    _objects = other.getObjects();
    _cameras = other.getCameras();
}

Scene::~Scene()
{
    _objects.clear();
    _cameras.clear();
}

void Scene::addObject(Object *object)
{
    _objects.push_back(object);
}

void Scene::addCamera(Camera &camera)
{
    _cameras.push_back(camera);
}

std::vector<Object *> Scene::getObjects() const
{
    return _objects;
}

std::vector<Object *> &Scene::getObjects()
{
    return _objects;
}

std::vector<Camera> Scene::getCameras() const
{
    return _cameras;
}

std::vector<Camera> &Scene::getCameras()
{
    return _cameras;
}

Object *Scene::getObject(int index) const
{
    return _objects.at(index);
}

Object *Scene::getObject(int index)
{
    return _objects.at(index);
}

Camera Scene::getCamera(int index) const
{
    return _cameras.at(index);
}

Camera &Scene::getCamera(int index)
{
    return _cameras.at(index);
}

Camera Scene::getMainCamera() const
{
    return _cameras.at(0);
}

Camera &Scene::getMainCamera()
{
    return _cameras.at(0);
}

void Scene::setObjects(std::vector<Object *> objects)
{
    _objects = std::move(objects);
}

void Scene::setCameras(std::vector<Camera> cameras)
{
    _cameras = std::move(cameras);
}
