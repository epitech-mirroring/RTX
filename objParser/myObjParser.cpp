/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** myObjParser
*/

#include "myObjParser.hpp"

void MyObjParser::loadMaterialFile(const std::string& filename, std::unordered_map<std::string, Material>& materials) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open material file: '" << filename << "'" << std::endl;
        return;
    }

    Material currentMaterial;
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        if (command == "newmtl") {
            if (!currentMaterial.name.empty()) {
                materials[currentMaterial.name] = currentMaterial;
            }
            iss >> currentMaterial.name;
        } else if (command == "Ka") {
            iss >> currentMaterial.ambient.x >> currentMaterial.ambient.y >> currentMaterial.ambient.z;
        } else if (command == "Kd") {
            iss >> currentMaterial.diffuse.x >> currentMaterial.diffuse.y >> currentMaterial.diffuse.z;
        } else if (command == "Ks") {
            iss >> currentMaterial.specular.x >> currentMaterial.specular.y >> currentMaterial.specular.z;
        } else if (command == "Ns") {
            iss >> currentMaterial.shininess;
        } else if (command == "map_Kd") {
            iss >> currentMaterial.diffuseMap;
        } else if (command == "illum") {
            iss >> currentMaterial.illuminationModel;
        } else if (command == "d" || command == "Tr") {
            iss >> currentMaterial.transparency;
        }
    }
    if (!currentMaterial.name.empty()) {
        materials[currentMaterial.name] = currentMaterial;
    }
    file.close();
}

void MyObjParser::loadObjFile(const std::string& filename, Mesh& mesh) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        if (command == "#") {
            std::cout << "Comment: " << line << std::endl;
        } else if (command == "v") {
            Vector3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            mesh.vertices.push_back(vertex);
        } else if (command == "vt") {
            Vector3 texCoord;
            iss >> texCoord.x >> texCoord.y;
            mesh.textureCoords.push_back(texCoord);
        } else if (command == "vn") {
            Vector3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            mesh.normals.push_back(normal);
        } else if (command == "o") {
            iss >> mesh.objectName;
        } else if (command == "g") {
            iss >> mesh.groupName;
        } else if (command == "s") {
            std::string smooth;
            iss >> smooth;
            mesh.smoothShading = smooth == "on";
        } else if (command == "f") {
            Face face;
            std::string vertex;
            while (iss >> vertex) {
                for (int i = 0; i < vertex.size(); i++) {
                    if (vertex[i] == '/') {
                        vertex[i] = ' ';
                    }
                }
                std::istringstream viss(vertex);
                int vi, ti = -1, ni = -1;
                viss >> vi >> ti >> ni;  // Assumes format v/t/n
                face.vertexIndices.push_back(vi);
                if (ni != -1) face.normalIndices.push_back(ni);
            }
            face.materialName = mesh.currentMaterialName;
            mesh.faces.push_back(face);
        } else if (command == "usemtl") {
            iss >> mesh.currentMaterialName;
        } else if (command == "mtllib") {
            std::string matFile;
            std::string path = line.substr(command.size() + 1);
            path.pop_back();
            path = filename.substr(0, filename.find_last_of("/\\") + 1) + path;
            loadMaterialFile(path, mesh.materials);
        }
    }
    file.close();
}