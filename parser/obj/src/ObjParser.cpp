/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** objParser
*/

#include "obj/ObjParser.hpp"

static std::vector<std::string> split(std::string s, const std::string& delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        tokens.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    if (!s.empty())
        tokens.push_back(s);
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

void ObjParser::parseUVs(const std::string& line)
{
    if (line.substr(0, 3) == "vt ") {
        float u, v = 0, w = 0;
        std::istringstream s(line.substr(3));
        std::vector<std::string> tokens = split(line.substr(3), " ");
        if (!tokens.empty()) {
            s >> u;
        } else {
            throw std::runtime_error("Invalid UV format: " + line);
        }
        if (tokens.size() >= 2)
            s >> v;
        if (tokens.size() >= 3)
            s >> w;
        uvsBuffer.emplace_back(glm::vec2(u, v));
    }
}

void ObjParser::parseFaces(const std::string& line)
{
    if (line.substr(0, 2) == "f ") {
        std::vector<std::string> tokens = split(line.substr(2), " ");
        if (tokens.size() >= 3) {
            std::vector<int> vertexIndices, normalIndices, textureIndices;
            for (auto& token : tokens) {
                auto parts = split(token, "/");
                if (parts.size() != 3) {
                    std::cerr << "Invalid face format: " << line << std::endl;
                    return;
                }
                if (!parts[0].empty())
                    vertexIndices.push_back(std::stoi(parts[0]) - 1);
                if (!parts[1].empty())
                    textureIndices.push_back(std::stoi(parts[1]) - 1);
                if (!parts[2].empty())
                    normalIndices.push_back(std::stoi(parts[2]) - 1);
            }
            for (size_t i = 2; i < vertexIndices.size(); i++) {
                Triangle triangle{};
                triangle.v0 = verticesBuffer[vertexIndices[0]];
                triangle.v1 = verticesBuffer[vertexIndices[i - 1]];
                triangle.v2 = verticesBuffer[vertexIndices[i]];
                if (!normalIndices.empty()) {
                    triangle.normalV0 = normalsBuffer[normalIndices[0]];
                    triangle.normalV1 = normalsBuffer[normalIndices[i - 1]];
                    triangle.normalV2 = normalsBuffer[normalIndices[i]];
                }
                if (!textureIndices.empty()) {
                    triangle.uv0 = uvsBuffer[textureIndices[0]];
                    triangle.uv1 = uvsBuffer[textureIndices[i - 1]];
                    triangle.uv2 = uvsBuffer[textureIndices[i]];
                }
                trianglesBuffer.push_back(triangle);
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
        parseUVs(line);
        parseFaces(line);
    }
    file.close();
    for (auto &triangle: trianglesBuffer) {
        // Axe Y is inverted in the raytracing engine
        triangle.v0.y = -triangle.v0.y;
        triangle.v1.y = -triangle.v1.y;
        triangle.v2.y = -triangle.v2.y;
        triangle.normalV0.y = -triangle.normalV0.y;
        triangle.normalV1.y = -triangle.normalV1.y;
        triangle.normalV2.y = -triangle.normalV2.y;

        triangle.v0.z = -triangle.v0.z;
        triangle.v1.z = -triangle.v1.z;
        triangle.v2.z = -triangle.v2.z;
        triangle.normalV0.z = -triangle.normalV0.z;
        triangle.normalV1.z = -triangle.normalV1.z;
        triangle.normalV2.z = -triangle.normalV2.z;
    }
    return new Object(objMaterial, objTransform, trianglesBuffer, textures);
}
