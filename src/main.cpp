/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include "Object.hpp"

int main(int argc, char **argv)
{
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

    GLFWwindow *window = glfwCreateWindow(800, 600, "RTX", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Error: Failed to create window" << std::endl;
        glfwTerminate();
        return 84;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Error: Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return 84;
    } else {
        std::cout << "GLAD initialized successfully" << std::endl;
    }

    // Load the fragment shader
    std::ifstream fragmentShaderFile("shaders/fragment.glsl");
    if (!fragmentShaderFile.is_open()) {
        std::cerr << "Error: Failed to open fragment shader file" << std::endl;
        glfwTerminate();
        return 84;
    } else {
        std::cout << "Fragment shader file opened successfully" << std::endl;
    }

    std::string fragmentShaderSource((std::istreambuf_iterator<char>(fragmentShaderFile)), std::istreambuf_iterator<char>());
    fragmentShaderFile.close();

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentShaderSourceCStr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, nullptr);
    glCompileShader(fragmentShader);
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Error: Failed to compile fragment shader\n" << infoLog << std::endl;
        glfwTerminate();
        return 84;
    } else {
        std::cout << "Fragment shader compiled successfully" << std::endl;
    }

    // Load shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Error: Failed to link shader program\n" << infoLog << std::endl;
        glfwTerminate();
        return 84;
    } else {
        std::cout << "Shader program linked successfully" << std::endl;
    }
    glDeleteShader(fragmentShader);

    Material screenMaterial;
    auto screen = Object(screenMaterial, Transform(), {0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f}, {0, 1, 2}, {});

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(screen.getVao());
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
