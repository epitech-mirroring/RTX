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
#include "../include/Object.hpp"

#pragma once

struct GLSL::Vector<3> {
    float x, y, z;
};

struct Material {
    std::string name;
    GLSL::Vector<3> ambient;
    GLSL::Vector<3> diffuse;
    GLSL::Vector<3> specular;
    float shininess;
    std::string diffuseMap;
    float transparency;
    int illuminationModel;
};

struct Face {
    std::vector<int> vertexIndices;
    std::vector<int> normalIndices;
    std::string materialName;
};

struct Mesh {
    std::vector<GLSL::Vector<3>> vertices;
    std::vector<GLSL::Vector<3>> normals;
    std::vector<Face> faces;
    std::vector<GLSL::Vector<3>> textureCoords;
    std::string objectName;
    std::string groupName;
    bool smoothShading = false;
    std::unordered_map<std::string, Material> materials;
    std::string currentMaterialName;
};

class MyObjParser {
    public:
        static void loadMaterialFile(const std::string& filename, std::unordered_map<std::string, Material>& materials);
        static Mesh loadObjFile(const std::string& filename);
        Object parseObjFile(const std::string& filename);
};
