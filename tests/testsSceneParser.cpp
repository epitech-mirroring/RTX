/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <criterion/criterion.h>
#include <iostream>
#include "SceneParser.hpp"
#include "primitives/Cube.hpp"
#include "primitives/Sphere.hpp"
#include "primitives/Rectangle.hpp"

Test(SceneParser, Color)
{
    std::string path = "scenes/tests/test.json";
    JsonObject root = JsonObject::parseFile(path);
    auto *colorJson = root.getValue<JsonObject>("color");
    glm::vec3 color = GlmParser::parseColor(colorJson);

    cr_assert_eq(color.x, 1.0);
    cr_assert_eq(color.y, 1.0);
    cr_assert_eq(color.z, 1.0);
}

Test(SceneParser, Quaternion)
{
    std::string path = "scenes/tests/test.json";
    JsonObject root = JsonObject::parseFile(path);
    auto *quaternionJson = root.getValue<JsonObject>("quaternion");
    glm::dquat quaternion = GlmParser::parseQuat(quaternionJson);

    cr_assert_eq(quaternion.w, 2.0);
    cr_assert_eq(quaternion.x, 2.0);
    cr_assert_eq(quaternion.y, 2.0);
    cr_assert_eq(quaternion.z, 1.0);
}

Test(SceneParser, Vector)
{
    std::string path = "scenes/tests/test.json";
    JsonObject root = JsonObject::parseFile(path);
    auto *vectorJson = root.getValue<JsonObject>("vector");
    glm::vec3 vector = GlmParser::parseVec3(vectorJson);

    cr_assert_eq(vector.x, 1.0);
    cr_assert_eq(vector.y, 1.0);
    cr_assert_eq(vector.z, 1.0);
}

Test(SceneParser, Material)
{
    std::string path = "scenes/tests/test.json";
    JsonObject root = JsonObject::parseFile(path);
    auto *materialJson = root.getValue<JsonObject>("material");
    Material material(materialJson);

    cr_assert_eq(material.getColor(), glm::vec3(1.0, 0.0, 0.0));
    cr_assert_eq(material.getEmission(), glm::vec3(0.0, 0.0, 0.0));
    cr_assert_eq(material.getBrightness(), 0.0);
    cr_assert_eq(material.getRoughness(), 1.0);
}

Test(SceneParser, Texture)
{
    std::string path = "scenes/tests/test.json";
    JsonObject root = JsonObject::parseFile(path);
    auto *textureJson = root.getValue<JsonObject>("texture");
    Texture texture(textureJson);

    cr_assert_eq(texture.getPath(), "test_texture.png");
    cr_assert_eq(texture.getType(), Texture::TextureType::NORMAL);
}

Test(SceneParser, Transform)
{
    std::string path = "scenes/tests/test.json";
    JsonObject root = JsonObject::parseFile(path);
    auto *transformJson = root.getValue<JsonObject>("transform");
    Transform transform(transformJson);

    cr_assert_eq(transform.getPosition(), glm::vec3(1.0, 1.0, 1.0));
    cr_assert_eq(transform.getScale(), glm::vec3(1.0, 1.0, 1.0));
}

Test(SceneParser, Camera)
{
    std::string path = "scenes/tests/test.json";
    JsonObject root = JsonObject::parseFile(path);
    auto *cameraJson = root.getValue<JsonObject>("camera");
    Camera camera(cameraJson);

    cr_assert_eq(camera.getFov(), 90.0);
    cr_assert_eq(camera.getNear(), 2.0);
    cr_assert_eq(camera.getAspect(), 1.0);
    cr_assert_eq(camera.getTransform().getPosition(), glm::vec3(1.0, 1.0, 1.0));
    cr_assert_eq(camera.getTransform().getScale(), glm::vec3(1.0, 1.0, 1.0));
}

Test(SceneParser, Wrong_Format)
{
    std::string path = "scenes/wrong.txt";
    SceneParser parser = SceneParser();

    cr_assert_throw(parser.setPath(path), std::invalid_argument);
}

Test(SceneParser, Wrong_File)
{
    std::string path = "scenes/wrong.json";
    SceneParser parser = SceneParser();

    parser.setPath(path);
    cr_assert_throw(parser.parse(), std::invalid_argument);
}

Test(SceneParser, Cameras)
{
    std::string path = "scenes/tests/testCameras.json";
    PropertiesFactory factory = PropertiesFactory();
    ObjectsFactory objFactory = ObjectsFactory();
    SceneParser parser = SceneParser(path, factory, objFactory);
    JsonObject root = JsonObject::parseFile(path);
    std::vector<Camera> cameras = SceneParser::parseCameras(root);

    cr_assert_eq(cameras.size(), 2);
    cr_assert_eq(cameras[0].getFov(), 90.0);
    cr_assert_eq(cameras[0].getAspect(), 1.0);
    cr_assert_eq(cameras[0].getNear(), 2.0);
    cr_assert_eq(cameras[0].getTransform().getPosition(), glm::vec3(1.0, 1.0, 1.0));
    cr_assert_eq(cameras[0].getTransform().getScale(), glm::vec3(1.0, 1.0, 1.0));
    cr_assert_eq(cameras[1].getFov(), 50.0);
    cr_assert_eq(cameras[1].getAspect(), 3.0);
    cr_assert_eq(cameras[1].getNear(), 3.0);
    cr_assert_eq(cameras[1].getTransform().getPosition(), glm::vec3(3.0, 3.0, 3.0));
    cr_assert_eq(cameras[1].getTransform().getScale(), glm::vec3(3.0, 3.0, 3.0));
}

Test(SceneParser, noCamera)
{
    std::string path = "scenes/tests/testNoCamera.json";
    PropertiesFactory factory = PropertiesFactory();
    ObjectsFactory objFactory = ObjectsFactory();
    SceneParser parser = SceneParser(path, factory, objFactory);
    JsonObject root = JsonObject::parseFile(path);

    cr_assert_throw(parser.parseCameras(root), std::invalid_argument);
}

Test(SceneParser, noCameras)
{
    std::string path = "scenes/tests/testNoCameras.json";
    PropertiesFactory factory = PropertiesFactory();
    ObjectsFactory objFactory = ObjectsFactory();
    SceneParser parser = SceneParser(path, factory, objFactory);
    JsonObject root = JsonObject::parseFile(path);

    cr_assert_throw(parser.parseCameras(root), std::invalid_argument);
}

Test(SceneParser, Cube)
{
    std::string path = "scenes/tests/testCube.json";
    JsonObject root = JsonObject::parseFile(path);
    auto *objectsJson = root.getValue<JsonArray>("objects");
    auto *cubeJson = objectsJson->getValue<JsonObject>(0);
    auto properties = RectangleProperties(cubeJson);
    Rectangle cube(properties);

    cr_assert_eq(cube.getMaterial().getColor(), glm::vec3(1.0, 0.0, 0.0));
    cr_assert_eq(cube.getMaterial().getEmission(), glm::vec3(0.0, 0.0, 0.0));
    cr_assert_eq(cube.getMaterial().getBrightness(), 0.0);
    cr_assert_eq(cube.getMaterial().getRoughness(), 1.0);
    cr_assert_eq(cube.getTransform().getPosition(), glm::vec3(1.0, 1.0, 1.0));
    cr_assert_eq(cube.getTransform().getScale(), glm::vec3(1.0, 1.0, 1.0));
    cr_assert_eq(cube.getTextures().at(Texture::TextureType::NORMAL).getPath(), "test_texture.png");
    cr_assert_eq(cube.getLength(), 1.0);
    cr_assert_eq(cube.getWidth(), 1.0);
    cr_assert_eq(cube.getHeight(), 1.0);
}

Test(SceneParser, ParseScene)
{
    std::string path = "scenes/tests/testScene.json";
    PropertiesFactory factory = PropertiesFactory();
    ObjectsFactory objFactory = ObjectsFactory();
    factory.registerProperties("cube", [](JsonObject *obj) { return new CubeProperties(obj); });
    objFactory.registerObject("cube", [](AbstractProperties &properties) -> Object * {return new Cube(dynamic_cast<CubeProperties &>(properties));});
    factory.registerProperties("sphere", [](JsonObject *obj) { return new SphereProperties(obj); });
    objFactory.registerObject("sphere", [](AbstractProperties &properties) -> Object * {return new Sphere(dynamic_cast<SphereProperties &>(properties));});
    SceneParser parser = SceneParser(path, factory, objFactory);
    parser.parse();

    cr_assert_eq(parser.getScene().isSkyBoxEnabled(), true);
    cr_assert_eq(parser.getScene().getObjects().size(), 1);
    cr_assert_eq(parser.getScene().getObjects()[0]->getMaterial().getColor(), glm::vec3(255.0, 0.0, 0.0));
    cr_assert_eq(parser.getScene().getObjects()[0]->getMaterial().getEmission(), glm::vec3(0.0, 0.0, 0.0));
    cr_assert_eq(parser.getScene().getObjects()[0]->getMaterial().getBrightness(), 0.0);
    cr_assert_eq(parser.getScene().getObjects()[0]->getMaterial().getRoughness(), 1.0);
    cr_assert_eq(parser.getScene().getObjects()[0]->getTransform().getPosition(), glm::vec3(1.0, 1.0, 6.0));
    cr_assert_eq(parser.getScene().getObjects()[0]->getTransform().getScale(), glm::vec3(1.0, 1.0, 1.0));
    cr_assert_eq(parser.getScene().getObjects()[0]->getTextures().at(Texture::TextureType::NORMAL).getPath(), "test_texture.png");
    cr_assert_eq(parser.getScene().getCameras().size(), 1);
    cr_assert_eq(parser.getScene().getCameras()[0].getFov(), 90.0);
    cr_assert_eq(parser.getScene().getCameras()[0].getAspect(), 1.0);
    cr_assert_eq(parser.getScene().getCameras()[0].getNear(), 2.0);
    cr_assert_eq(parser.getScene().getCameras()[0].getTransform().getPosition(), glm::vec3(1.0, 1.0, 1.0));
    cr_assert_eq(parser.getScene().getCameras()[0].getTransform().getScale(), glm::vec3(1.0, 1.0, 1.0));
}

Test(SceneParser, ParseSphere)
{
    std::string path = "scenes/tests/testSphere.json";
    JsonObject root = JsonObject::parseFile(path);
    auto *objectsJson = root.getValue<JsonArray>("objects");
    auto *sphereJson = objectsJson->getValue<JsonObject>(0);
    auto properties = SphereProperties(sphereJson);
    Sphere sphere(properties);

    cr_assert_eq(sphere.getMaterial().getColor(), glm::vec3(255.0, 0.0, 0.0));
    cr_assert_eq(sphere.getMaterial().getEmission(), glm::vec3(0.0, 0.0, 0.0));
    cr_assert_eq(sphere.getMaterial().getBrightness(), 0.0);
    cr_assert_eq(sphere.getMaterial().getRoughness(), 1.0);
    cr_assert_eq(sphere.getTransform().getPosition(), glm::vec3(1.0, 1.0, 6.0));
    cr_assert_eq(sphere.getTransform().getScale(), glm::vec3(1.0, 1.0, 1.0));
    cr_assert_eq(sphere.getTextures().at(Texture::TextureType::NORMAL).getPath(), "test_texture.png");
    cr_assert_eq(sphere.getProperties().getRadius() , 10.0);
    std::cout << sphere.getTriangles().size() << std::endl;
    cr_assert_eq(sphere.getTriangles().size(), 1280);
}
