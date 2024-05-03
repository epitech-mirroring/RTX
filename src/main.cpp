/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Application.hpp"
#include "primitives/Cube.hpp"
#include <iostream>

#define WIDTH 800.0f
#define HEIGHT 600.0f

int main(int argc, char **argv)
{
    Scene scene;
    // Camera
    Transform cameraTransform;
    cameraTransform.setPosition({0.0f, 0.0f, 5.0f});
    cameraTransform.rotate({0.0f, -1.0f, 0.0f}, M_PI);
    Camera camera(cameraTransform, 60.0f, WIDTH / HEIGHT, 0.1f);
    scene.addCamera(camera);

    // Cube
    Transform cubeTransform;
    cubeTransform.setPosition({0.0f, 0.0f, 0.0f});
    Material cubeMaterial;
    Cube *cube = new Cube(cubeMaterial, cubeTransform, {}, 1.0f);
    scene.addObject(cube);

    Application app(WIDTH, HEIGHT, "RTX", &scene);

    app.run([&scene]() {
        for (auto &object : scene.getObjects()) {
            object->getTransform().rotate({0.0f, 1.0f, 0.0f}, 0.05f);
        }
    });
    return 0;
}