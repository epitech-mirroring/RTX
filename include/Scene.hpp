/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Object.hpp"
#include "Camera.hpp"
#include <vector>

class Scene {
    protected:
        std::vector<Object *> _objects;
        std::vector<Camera> _cameras;
        bool _skyBoxEnabled = true;
    public:
        Scene();
        Scene(Scene const &other);
        ~Scene();
        void addObject(Object *object);
        void addCamera(Camera &camera);
        [[nodiscard]] std::vector<Object *> getObjects() const;
        [[nodiscard]] std::vector<Object *> &getObjects();
        [[nodiscard]] std::vector<Camera> getCameras() const;
        [[nodiscard]] std::vector<Camera> &getCameras();
        [[nodiscard]] Object *getObject(int index) const;
        [[nodiscard]] Object *getObject(int index);
        [[nodiscard]] Camera getCamera(int index) const;
        [[nodiscard]] Camera &getCamera(int index);
        [[nodiscard]] Camera getMainCamera() const;
        [[nodiscard]] Camera &getMainCamera();
        void setObjects(std::vector<Object *> objects);
        void setCameras(std::vector<Camera> cameras);
        void setSkyBoxEnabled(bool enabled);
        [[nodiscard]] bool isSkyBoxEnabled() const;
};
