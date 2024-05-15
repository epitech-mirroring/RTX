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
#include "primitives/Cube.hpp"
#include "primitives/Rectangle.hpp"
#include "primitives/Plane.hpp"
#include "primitives/Cylinder.hpp"
#include "primitives/Cone.hpp"
#include "primitives/Torus.hpp"
#include "Raytracer.hpp"
#include "json/Json.hpp"
#include "primitives/Plane.hpp"
#include <iostream>
#include <fstream>

static Arguments parseArgs(int argc, char **argv)
{
    Arguments args;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-f" || arg == "--fast" || arg == "--auto-quit") {
            args.quit_after_render = true;
        } else if (arg == "--frames") {
            if (i + 1 >= argc) {
                std::cerr << "Missing argument for --frames" << std::endl;
                exit(84);
            }
            args.frame_before_render = std::stoi(argv[i + 1]);
            if (args.frame_before_render < 1) {
                std::cerr << "Invalid argument for --frames" << std::endl;
                exit(84);
            }
            i++;
        } else if (arg == "-x" || arg == "--disable-screenshot") {
            args.disable_render_output = true;
        } else if (arg == "-s" || arg == "--size") {
            if (i + 1 >= argc) {
                std::cerr << "Missing argument for --size" << std::endl;
                exit(84);
            }
            std::string size = argv[i + 1];
            size_t pos = size.find('x');
            if (pos == std::string::npos) {
                std::cerr << "Invalid size format" << std::endl;
                exit(84);
            }
            args.width = std::stoi(size.substr(0, pos));
            args.height = std::stoi(size.substr(pos + 1));
            i++;
        } else if (arg == "-h" || arg == "--help") {
            std::cerr << "Usage: ./raytracer \"scene file\"" << std::endl;
            std::cerr << "Options:" << std::endl;
            std::cerr << "  -f --fast --auto-quit: Automatically quit after the screenshot is taken" << std::endl;
            std::cerr << "  --frames N: Set the number of frame before taking the screenshot" << std::endl;
            std::cerr << "  -x --disable-screenshot: Disable the screenshot" << std::endl;
            std::cerr << "  -s --size WIDTHxHEIGHT: Set the size of the window" << std::endl;
            std::cerr << "  -o --output PATH: Set the output path of the screenshot" << std::endl;
            std::cerr << "  -q --quiet: Disable warning messages" << std::endl;
            std::cerr << "  -h --help: Display this help message" << std::endl;
            exit(0);
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 >= argc) {
                std::cerr << "Missing argument for --output" << std::endl;
                exit(84);
            }
            args.outputPath = argv[i + 1];
            i++;
        } else if (arg == "-q" || arg == "--quiet") {
            args.quiet = true;
        } else {
            if (arg[0] == '-') {
                std::cerr << "Unknown option: " << arg << std::endl;
                exit(84);
            }
            args.scenePath = arg;
        }
    }
    return args;
}

static void fillFactory(ObjectsFactory &objFactory, PropertiesFactory &propFactory)
{
    objFactory.registerObject("cube", [](AbstractProperties &properties) -> Object * {return new Cube(dynamic_cast<CubeProperties &>(properties));});
    objFactory.registerObject("rectangle", [](AbstractProperties &properties) -> Object * {return new Rectangle(dynamic_cast<RectangleProperties &>(properties));});
    objFactory.registerObject("plane", [](AbstractProperties &properties) -> Object * {return new Plane(dynamic_cast<PlaneProperties &>(properties));});
    objFactory.registerObject("sphere", [](AbstractProperties &properties) -> Object * {return new Sphere(dynamic_cast<SphereProperties &>(properties));});
    objFactory.registerObject("cylinder", [](AbstractProperties &properties) -> Object * {return new Cylinder(dynamic_cast<CylinderProperties &>(properties));});
    objFactory.registerObject("cone", [](AbstractProperties &properties) -> Object * {return new Cone(dynamic_cast<ConeProperties &>(properties));});
    objFactory.registerObject("sphere", [](AbstractProperties &properties) -> Object * {return new Sphere(dynamic_cast<SphereProperties &>(properties));});
    objFactory.registerObject("torus", [](AbstractProperties &properties) -> Object * {return new Torus(dynamic_cast<TorusProperties &>(properties));});
    propFactory.registerProperties("cube", [](JsonObject *obj) { return new CubeProperties(obj); });
    propFactory.registerProperties("rectangle", [](JsonObject *obj) { return new RectangleProperties(obj); });
    propFactory.registerProperties("plane", [](JsonObject *obj) { return new PlaneProperties(obj); });
    propFactory.registerProperties("cylinder", [](JsonObject *obj) { return new CylinderProperties(obj); });
    propFactory.registerProperties("cone", [](JsonObject *obj) { return new ConeProperties(obj); });
    propFactory.registerProperties("sphere", [](JsonObject *obj) { return new SphereProperties(obj); });
    propFactory.registerProperties("torus", [](JsonObject *obj) { return new TorusProperties(obj); });
}

static void checkOverwritingOutput(const std::string &outputPath, bool quiet)
{
    std::ifstream file(outputPath);
    if (file.is_open()) {
        if (!quiet) {
            std::cerr << "Caution: " << outputPath << " already exists, it will be overwritten" << std::endl;
            std::cerr << "To disable this message, use -q or --quiet" << std::endl;
        }
        file.close();
    }
}

int main(int argc, char **argv)
{
    Arguments args = parseArgs(argc, argv);
    if (args.scenePath.empty()) {
        std::cerr << "Missing scene file" << std::endl;
        return 84;
    }
    checkOverwritingOutput(args.outputPath, args.quiet);
    ObjectsFactory objFactory = ObjectsFactory();
    PropertiesFactory propFactory = PropertiesFactory();
    fillFactory(objFactory, propFactory);
    SceneParser parser = SceneParser(args.scenePath, propFactory, objFactory);
    parser.parse();
    Scene scene = parser.getScene();

    Application app(args.width, args.height, "RTX", &scene);

    bool saved = false;

    app.run([&app, &saved, &args, &scene]() {
        if (app.getFrameIndex() >= args.frame_before_render && !saved && !args.disable_render_output) {
            app.screenshot(args.outputPath);
            saved = true;

            if (args.quit_after_render) {
                app.stop();
            }
        }

        Object *obj = scene.getObject(0);
        obj->getTransform().rotate(glm::vec3(0, 1, 0), 0.01);
        app.updateScene();
    });
    return 0;
}
