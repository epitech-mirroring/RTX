/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** objParser
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Object.hpp"

#pragma once

// will be used to store every data related to the texture

struct objMaterial {
    std::string name;
    std::vector<glm::vec3> ambient;
    std::vector<glm::vec3> diffuse;
    std::vector<glm::vec3> specular;
    float shininess;
    std::string diffuseMap;
    float transparency;
    int illuminationModel;
};

class objParser {
    public:
        Object *parseFile(const std::string& filename);
        void parseVertices(const std::string& line);
        void parseNormals(const std::string& line);
        void parseFaces(const std::string& line);
    private:
        std::vector<glm::vec3> verticesBuffer;
        std::vector<glm::vec3> normalsBuffer;
        std::vector<Triangle> trianglesBuffer;
};
