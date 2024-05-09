/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** objParser
*/

#include "obj/ObjParser.hpp"

static std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

static glm::vec3 parseVec3(const std::string& line) {
    std::istringstream s(line);
    glm::vec3 v;
    s >> v.x >> v.y >> v.z;
    return v;
}

void ObjParser::parseVertices(const std::string& line)
{
    if (line.substr(0, 2) == "v ")
        verticesBuffer.push_back(parseVec3(line.substr(2)));
}

void ObjParser::parseNormals(const std::string& line)
{
    if (line.substr(0, 3) == "vn ")
        normalsBuffer.push_back(parseVec3(line.substr(3)));
}

void ObjParser::parseFaces(const std::string& line)
{
    if (line.substr(0, 2) == "f ") {
        std::vector<std::string> tokens = split(line.substr(2), ' ');
        if (tokens.size() >= 3) {
            Triangle tri{};
            std::vector<int> vertexIndices, normalIndices;
            for (auto& token : tokens) {
                auto parts = split(token, '/');
                if (!parts.empty() && !parts[0].empty()) {
                    vertexIndices.push_back(std::stoi(parts[0]) - 1);
                }
                if (parts.size() == 3 && !parts[2].empty()) {
                    normalIndices.push_back(std::stoi(parts[2]) - 1);
                }
            }
            if (vertexIndices.size() == 3) {
                tri.v0 = verticesBuffer[vertexIndices[0]];
                tri.v1 = verticesBuffer[vertexIndices[1]];
                tri.v2 = verticesBuffer[vertexIndices[2]];

                if (normalIndices.size() == 3) {
                    tri.normalV0 = normalsBuffer[normalIndices[0]];
                    tri.normalV1 = normalsBuffer[normalIndices[1]];
                    tri.normalV2 = normalsBuffer[normalIndices[2]];
                } else {
                    glm::vec3 edge1 = tri.v1 - tri.v0;
                    glm::vec3 edge2 = tri.v2 - tri.v0;
                    glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));
                    tri.normalV0 = tri.normalV1 = tri.normalV2 = normal;
                }
                trianglesBuffer.push_back(tri);
            }
        }
    }
}

Object *ObjParser::parseFile(const std::string& filename)
{
    // remain to implement texture
    Transform objTransform;
    Material objMaterial;
    std::vector<Texture> textures;

    std::string line;
    std::ifstream file(filename);

    if (filename.substr(filename.find_last_of('.') + 1) != "obj") {
        std::cerr << "Invalid file format: " << filename << std::endl;
        return nullptr;
    }
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << filename << std::endl;
        return nullptr;
    }
    trianglesBuffer.clear();
    verticesBuffer.clear();
    normalsBuffer.clear();
    while (getline(file, line)) {
        parseVertices(line);
        parseNormals(line);
        parseFaces(line);
    }
    file.close();
    return new Object(objMaterial, objTransform, trianglesBuffer, textures);
}
