/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Application.hpp"
#include "SceneParser.hpp"
#include "primitives/Cube.hpp"
#include "primitives/Rectangle.hpp"
#include <iostream>

#define WIDTH 800.0f
#define HEIGHT 600.0f

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: ./rtx \"scene file\"" << std::endl;
        return 84;
    }
    ObjectsFactory objFactory = ObjectsFactory();
    PropertiesFactory propFactory = PropertiesFactory();
    objFactory.registerObject("cube", [](AbstractProperties &properties) -> Object * {return new Cube(dynamic_cast<CubeProperties &>(properties));});
    objFactory.registerObject("rectangle", [](AbstractProperties &properties) -> Object * {return new Rectangle(dynamic_cast<RectangleProperties &>(properties));});
    propFactory.registerProperties("cube", [](JsonObject *obj) { return new CubeProperties(obj); });
    propFactory.registerProperties("rectangle", [](JsonObject *obj) { return new RectangleProperties(obj); });
    std::string path = std::string(argv[1]);
    SceneParser parser = SceneParser(path, propFactory, objFactory);
    parser.parse();
    Scene scene = parser.getScene();

    Application app(WIDTH, HEIGHT, "RTX", &scene);

    app.run([&scene]() {
    });
    return 0;
}
