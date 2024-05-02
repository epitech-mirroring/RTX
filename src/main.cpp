/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Camera.hpp"
#include "GLSL/Shader.hpp"
#include "Object.hpp"

#define WIDTH 800.0f
#define HEIGHT 600.0f

struct Triangle {
    glm::vec3 v0;
    glm::vec3 v1;
    glm::vec3 v2;
    glm::vec3 normalV0;
    glm::vec3 normalV1;
    glm::vec3 normalV2;
};

struct Mesh {
    unsigned int startIdx;
    unsigned int endIdx;
    glm::vec3 boundingBoxMin;
    glm::vec3 boundingBoxMax;
};

Camera *g_camera;
double oldX = 0.0;
double oldY = 0.0;

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    (void)window;
    if (oldX == 0.0 && oldY == 0.0) {
        oldX = xpos;
        oldY = ypos;
    } else {
        g_camera->getTransform().rotate((float)(ypos - oldY) / 100.f, (float)(xpos - oldX) / 100.f, 0.0f);
        oldX = xpos;
        oldY = ypos;
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        g_camera->getTransform().translate(0.0f, 0.0f, -0.01f);
    } else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        g_camera->getTransform().translate(0.0f, 0.0f, 0.01f);
    } else if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        g_camera->getTransform().translate(-0.01f, 0.0f, 0.0f);
    } else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        g_camera->getTransform().translate(0.01f, 0.0f, 0.0f);
    } else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        g_camera->getTransform().translate(0.0f, 0.01f, 0.0f);
    } else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
        g_camera->getTransform().translate(0.0f, -0.01f, 0.0f);
    }

}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    if (glfwInit() == GLFW_FALSE) {
        std::cerr << "Error: Failed to initialize GLFW" << std::endl;
        return 84;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow((int) WIDTH, (int) HEIGHT, "RTX", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Error: Failed to create window" << std::endl;
        glfwTerminate();
        return 84;
    }
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Error: Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return 84;
    } else {
        std::cout << "GLAD initialized successfully" << std::endl;
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    }

    GLSL::Shader raytracingShader(GLSL::Shader::Type::FRAGMENT, "shaders/raytracing.frag");
    GLSL::Shader screenShader(GLSL::Shader::Type::VERTEX, "shaders/screen.vert");
    Material screenMaterial;
    auto screen = Object(screenMaterial, Transform(), {
            {-1.0f, -1.0f, 0.0f},
            {1.0f, -1.0f, 0.0f},
            {1.0f, 1.0f, 0.0f},
            {-1.0f, 1.0f, 0.0f}
    }, {
            0, 1, 2,
            2, 3, 0
    }, {});

    Transform transform;
    Camera camera(transform, 60.0f, HEIGHT / WIDTH, 1.f);
    g_camera = &camera;

    Triangle triangles[] = {
            {
                    {0.0f, 0.0f, 10.0f},
                    {-2.5f, 0.0f, 5.0f},
                    {2.5f, 0.0f, 5.0f},
                    {0.0f, 1.0f, 0.0f},
                    {0.0f, 1.0f, 0.0f},
                    {0.0f, 1.0f, 0.0f}
            }
    };

    Mesh meshes[] = {
            {
                    0,
                    1,
                    {-2.5f, 0.0f, 5.0f},
                    {2.5f, 0.0f, 10.0f}
            }
    };

    GLuint triangleBuffer;
    glGenBuffers(1, &triangleBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, triangleBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Triangle) * 1, triangles, GL_STATIC_DRAW);

    GLuint meshBuffer;
    glGenBuffers(1, &meshBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, meshBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Mesh) * 1, meshes, GL_STATIC_DRAW);


    glViewport(0, 0, (int) WIDTH * 2, (int) HEIGHT * 2);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        screen.draw(screenShader, raytracingShader, [camera, triangleBuffer, meshBuffer](const GLSL::Shader &vertexShader, const GLSL::Shader &fragmentShader) {
            vertexShader.setVec2("iResolution", glm::vec2(WIDTH * 2, HEIGHT * 2));
            fragmentShader.setVec2("iResolution", glm::vec2(WIDTH * 2, HEIGHT * 2));
            fragmentShader.setVec3("iViewPlaneParams", camera.getViewParams());
            fragmentShader.setVec3("iCameraPosition", camera.getTransform().getPosition());
            fragmentShader.setMat4("iCameraMatrix", camera.getTransform().getTransformationMatrix());
            fragmentShader.setUInt("iNumTriangles", 1);
            fragmentShader.setUInt("iNumMeshes", 1);

            glBindBufferBase(GL_UNIFORM_BUFFER, 1, triangleBuffer);
            glBindBufferBase(GL_UNIFORM_BUFFER, 2, meshBuffer);
        });

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}