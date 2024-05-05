/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** myObjParser
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

class MyObjParser {
    public:
        Object *parseFile(const std::string& filename);
};
