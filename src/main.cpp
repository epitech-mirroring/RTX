/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

#define WIDTH 1920
#define HEIGHT 1080

const float deg2Rad = 3.14159265358979323846f / 180.0f;

struct Camera {
    sf::Glsl::Vec3 position;
    sf::Glsl::Vec3 rotation;
    float fieldOfView = 60;
};

sf::Glsl::Mat4 Translation(sf::Glsl::Vec3 translation)
{
    sf::Glsl::Mat4 matrix = sf::Transform::Identity;
    matrix.array[3*4 + 0] = translation.x;
    matrix.array[3*4 + 1] = translation.y;
    matrix.array[3*4 + 2] = translation.z;
    return matrix;
}

sf::Glsl::Mat4 Rotation(sf::Glsl::Vec3 rotation)
{
    sf::Glsl::Mat4 matrix = sf::Transform::Identity;
    matrix.array[0*4 + 0] = cos(rotation.y) * cos(rotation.z);
    matrix.array[0*4 + 1] = cos(rotation.y) * sin(rotation.z);
    matrix.array[0*4 + 2] = -sin(rotation.y);
    matrix.array[1*4 + 0] = sin(rotation.x) * sin(rotation.y) * cos(rotation.z) - cos(rotation.x) * sin(rotation.z);
    matrix.array[1*4 + 1] = sin(rotation.x) * sin(rotation.y) * sin(rotation.z) + cos(rotation.x) * cos(rotation.z);
    matrix.array[1*4 + 2] = sin(rotation.x) * cos(rotation.y);
    matrix.array[2*4 + 0] = cos(rotation.x) * sin(rotation.y) * cos(rotation.z) + sin(rotation.x) * sin(rotation.z);
    matrix.array[2*4 + 1] = cos(rotation.x) * sin(rotation.y) * sin(rotation.z) - sin(rotation.x) * cos(rotation.z);
    matrix.array[2*4 + 2] = cos(rotation.x) * cos(rotation.y);
    return matrix;
}

sf::Glsl::Mat4 MatrixMultiply(sf::Glsl::Mat4 a, sf::Glsl::Mat4 b)
{
    sf::Glsl::Mat4 matrix = sf::Transform::Identity;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            matrix.array[i*4 + j] = a.array[i*4 + 0] * b.array[0*4 + j] + a.array[i*4 + 1] * b.array[1*4 + j] + a.array[i*4 + 2] * b.array[2*4 + j] + a.array[i*4 + 3] * b.array[3*4 + j];
    return matrix;
}

// Function that return a 4x4 transform matrix to transform camera local space to world space
sf::Glsl::Mat4 CameraLocalToWorldMatrix(const Camera &camera)
{
    sf::Glsl::Mat4 translation = Translation(camera.position);
    sf::Glsl::Mat4 rotation = Rotation(camera.rotation);
    return MatrixMultiply(rotation, translation);
}

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "RTX");
    sf::Shader shader;
    sf::RectangleShape fullscreenRect = sf::RectangleShape(sf::Vector2f(WIDTH, HEIGHT));
    fullscreenRect.setFillColor(sf::Color::White);
    fullscreenRect.setPosition(0, 0);
    Camera camera = {sf::Glsl::Vec3(0, 0, 0), sf::Glsl::Vec3(0, 0, 0)};
    float nearClipPlane = 1;
    float planeHeight = nearClipPlane * tan(camera.fieldOfView * 0.5f * deg2Rad) * 2.0f;
    float planeWidth = planeHeight * ((float) WIDTH / (float) HEIGHT);
    bool mousePressed = false;
    int lastMouseX = 0;
    int lastMouseY = 0;

    shader.loadFromFile("shaders/fragment.glsl", sf::Shader::Fragment);
    while (window.isOpen()) {
        sf::Event event = {};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                mousePressed = true;
            if (event.type == sf::Event::MouseButtonReleased)
                mousePressed = false;
            if (event.type == sf::Event::MouseMoved) {
                if (mousePressed) {
                camera.rotation.y +=
                        (float) (event.mouseMove.x - lastMouseX) * 0.01f;
                camera.rotation.x +=
                        (float) (event.mouseMove.y - lastMouseY) * 0.01f;
                }
                lastMouseX = event.mouseMove.x;
                lastMouseY = event.mouseMove.y;
            }

        }
        window.clear();
        // Draw here
        shader.setUniform("u_time", (float) std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
        shader.setUniform("u_resolution", sf::Glsl::Vec2(WIDTH, HEIGHT));
        shader.setUniform("cameraPosition", camera.position);
        shader.setUniform("cameraLocalToWorldMatrix", CameraLocalToWorldMatrix(camera));
        shader.setUniform("viewParams", sf::Glsl::Vec3(planeWidth, planeHeight, nearClipPlane));
        window.draw(fullscreenRect, &shader);
        window.display();
    }
}
