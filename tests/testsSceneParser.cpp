/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <criterion/criterion.h>
#include "SceneParser.hpp"
#include <iostream>

#define TEST_JSON "scenes/tests/test.json"

Test(SceneParser, Color)
{
    std::string path = TEST_JSON;
    SceneParser parser = SceneParser(path);
    JsonObject root = JsonObject::parseFile(path);
    auto *colorJson = root.getValue<JsonObject>("color");
    GLSL::Color color(colorJson);

    cr_assert_eq(color.getR(), 1.0);
    cr_assert_eq(color.getG(), 1.0);
    cr_assert_eq(color.getB(), 1.0);
    cr_assert_eq(color.getA(), 1.0);
}

Test(SceneParser, Quaternion)
{
    std::string path = TEST_JSON;
    SceneParser parser = SceneParser(path);
    JsonObject root = JsonObject::parseFile(path);
    auto *quaternionJson = root.getValue<JsonObject>("quaternion");
    GLSL::Quaternion quaternion(quaternionJson);

    cr_assert_eq(quaternion.x, 2.0);
    cr_assert_eq(quaternion.y, 2.0);
    cr_assert_eq(quaternion.z, 2.0);
    cr_assert_eq(quaternion.w, 1.0);
}

Test(SceneParser, Vector)
{
    std::string path = TEST_JSON;
    SceneParser parser = SceneParser(path);
    JsonObject root = JsonObject::parseFile(path);
    auto *vectorJson = root.getValue<JsonArray>("vector");
    GLSL::Vector<3> vector(vectorJson);

    cr_assert_eq(vector[0], 1.0);
    cr_assert_eq(vector[1], 1.0);
    cr_assert_eq(vector[2], 1.0);
}

Test(SceneParser, Material)
{
    std::string path = TEST_JSON;
    SceneParser parser = SceneParser(path);
    JsonObject root = JsonObject::parseFile(path);
    auto *materialJson = root.getValue<JsonObject>("material");
    Material material(materialJson);

    cr_assert_eq(material.getColor(), GLSL::Color(1.0, 0.0, 0.0, 1.0));
    cr_assert_eq(material.getEmission(), GLSL::Color(0.0, 0.0, 0.0, 1.0));
    cr_assert_eq(material.getBrightness(), 0.0);
    cr_assert_eq(material.getRoughness(), 1.0);
}

Test(SceneParser, Texture)
{
    std::string path = TEST_JSON;
    SceneParser parser = SceneParser(path);
    JsonObject root = JsonObject::parseFile(path);
    auto *textureJson = root.getValue<JsonObject>("texture");
    Texture texture(textureJson);

    cr_assert_eq(texture.getPath(), "test_texture.png");
    cr_assert_eq(texture.getType(), Texture::TextureType::NORMAL);
}

Test(SceneParser, Transform)
{
    std::string path = TEST_JSON;
    SceneParser parser = SceneParser(path);
    JsonObject root = JsonObject::parseFile(path);
    auto *transformJson = root.getValue<JsonObject>("transform");
    Transform transform(transformJson);

    cr_assert_eq(transform.getPosition(), GLSL::Vector<3>(1.0, 1.0, 1.0));
    cr_assert_eq(transform.getRotation(), GLSL::Quaternion(1.0, 1.0, 1.0, 1.0));
    cr_assert_eq(transform.getScale(), GLSL::Vector<3>(1.0, 1.0, 1.0));
}

Test(SceneParser, Camera)
{
    std::string path = TEST_JSON;
    SceneParser parser = SceneParser(path);
    JsonObject root = JsonObject::parseFile(path);
    auto *cameraJson = root.getValue<JsonObject>("camera");
    Camera camera(cameraJson);

    cr_assert_eq(camera.getFov(), 90.0);
    cr_assert_eq(camera.getNear(), 2.0);
    cr_assert_eq(camera.getAspect(), 1.0);
    cr_assert_eq(camera.getTransform().getPosition(), GLSL::Vector<3>(1.0, 1.0, 1.0));
    cr_assert_eq(camera.getTransform().getRotation(), GLSL::Quaternion(1.0, 1.0, 1.0, 1.0));
    cr_assert_eq(camera.getTransform().getScale(), GLSL::Vector<3>(1.0, 1.0, 1.0));
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
    SceneParser parser = SceneParser(path);
    JsonObject root = JsonObject::parseFile(path);
    std::vector<Camera> cameras = parser.parseCameras(root);

    cr_assert_eq(cameras.size(), 2);
    cr_assert_eq(cameras[0].getFov(), 90.0);
    cr_assert_eq(cameras[0].getAspect(), 1.0);
    cr_assert_eq(cameras[0].getNear(), 2.0);
    cr_assert_eq(cameras[0].getTransform().getPosition(), GLSL::Vector<3>(1.0, 1.0, 1.0));
    cr_assert_eq(cameras[0].getTransform().getRotation(), GLSL::Quaternion(1.0, 1.0, 1.0, 1.0));
    cr_assert_eq(cameras[0].getTransform().getScale(), GLSL::Vector<3>(1.0, 1.0, 1.0));
    cr_assert_eq(cameras[1].getFov(), 50.0);
    cr_assert_eq(cameras[1].getAspect(), 3.0);
    cr_assert_eq(cameras[1].getNear(), 3.0);
    cr_assert_eq(cameras[1].getTransform().getPosition(), GLSL::Vector<3>(3.0, 3.0, 3.0));
    cr_assert_eq(cameras[1].getTransform().getRotation(), GLSL::Quaternion(3.0, 3.0, 3.0, 3.0));
    cr_assert_eq(cameras[1].getTransform().getScale(), GLSL::Vector<3>(3.0, 3.0, 3.0));
}

Test(SceneParser, noCamera)
{
    std::string path = "scenes/tests/testNoCamera.json";
    SceneParser parser = SceneParser(path);
    JsonObject root = JsonObject::parseFile(path);

    cr_assert_throw(parser.parseCameras(root), std::invalid_argument);
}

Test(SceneParser, noCameras)
{
    std::string path = "scenes/tests/testNoCameras.json";
    SceneParser parser = SceneParser(path);
    JsonObject root = JsonObject::parseFile(path);

    cr_assert_throw(parser.parseCameras(root), std::invalid_argument);
}
