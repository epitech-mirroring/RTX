/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Application.hpp"
#include "SceneParser.hpp"
#include "primitives/Sphere.hpp"
#include <iostream>

#define WIDTH 800.0f
#define HEIGHT 600.0f

int main(int argc, char **argv)
{
    Scene scene;
    std::string filename;
    if (argc > 1) {
        filename = argv[1];
    }
    else {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 84;
    }
    PropertiesFactory propertiesFactory;
    ObjectsFactory objectsFactory;
    propertiesFactory.registerProperties("sphere", [](JsonObject *obj) {
        return new SphereProperties(obj);
    });
    objectsFactory.registerObject("sphere", [](AbstractProperties &properties) -> Object *{
        return new Sphere(dynamic_cast<SphereProperties &>(properties));
    });
    SceneParser parser(filename, propertiesFactory, objectsFactory);
    parser.parse();
    scene = parser.getScene();
    Application app(WIDTH, HEIGHT, "RTX", &scene);

    app.run([&scene]() {
        for (auto &object : scene.getObjects()) {
            object->getTransform().rotate({0.0f, 1.0f, 0.0f}, 0.05f);
        }
    });
    return 0;
}
