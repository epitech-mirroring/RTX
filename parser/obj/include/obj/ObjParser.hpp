/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** objParser
*/


#pragma once
#include "Object.hpp"
#include "AbstractParser.hpp"

// will be used to store every data related to the texture

struct ObjMaterial {
    std::string name;
    std::vector<glm::vec3> ambient;
    std::vector<glm::vec3> diffuse;
    std::vector<glm::vec3> specular;
    float shininess;
    std::string diffuseMap;
    float transparency;
    int illuminationModel;
};

class ObjParser : public AbstractParser {
    public:
        Object *parseFile(const std::string& filename) override;
        void parseVertices(const std::string& line) override;
        void parseNormals(const std::string& line) override;
        void parseFaces(const std::string& line) override;
        ~ObjParser() override = default;
    private:
        std::vector<glm::vec3> verticesBuffer;
        std::vector<glm::vec3> normalsBuffer;
        std::vector<Triangle> trianglesBuffer;
};
