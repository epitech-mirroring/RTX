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

#pragma once

struct Vector3 {
    float x, y, z;
};

struct Material {
    std::string name;
    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
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
    std::vector<Vector3> vertices;
    std::vector<Vector3> normals;
    std::vector<Face> faces;
    std::vector<Vector3> textureCoords;
    std::string objectName;
    std::string groupName;
    bool smoothShading = false;
    std::unordered_map<std::string, Material> materials;
    std::string currentMaterialName;
};

class MyObjParser {
    public:
        static void loadMaterialFile(const std::string& filename, std::unordered_map<std::string, Material>& materials);
        static void loadObjFile(const std::string& filename, Mesh& mesh);
};
