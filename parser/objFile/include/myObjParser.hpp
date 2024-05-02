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

struct objVector3 {
    float x, y, z;
};

struct objMaterial {
    std::string name;
    objVector3 ambient;
    objVector3 diffuse;
    objVector3 specular;
    float shininess;
    std::string diffuseMap;
    float transparency;
    int illuminationModel;
};

struct objFace {
    std::vector<int> vertexIndices;
    std::vector<int> normalIndices;
    std::string materialName;
};

struct Mesh {
    std::vector<GLSL::Vector<3>> vertices;
    std::vector<GLSL::Vector<3>> normals;
    std::vector<objFace> faces;
    std::vector<GLSL::Vector<3>> textureCoords;
    std::string objectName;
    std::string groupName;
    bool smoothShading = false;
    std::unordered_map<std::string, objMaterial> materials;
    std::string currentMaterialName;
};

class MyObjParser {
    public:
        static void loadMaterialFile(const std::string& filename,
            std::unordered_map<std::string, objMaterial>& materials);
        static Mesh loadObjFile(const std::string& filename);
        Object parseObjFile(const std::string& filename);
};
