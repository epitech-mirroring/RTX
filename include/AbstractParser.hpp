/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** abstractParser
*/

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Object.hpp"
#include "Material.hpp"
#include "Transform.hpp"

class AbstractParser {
    public:
        virtual Object *parseFile(const std::string& filename) = 0;
        virtual void parseVertices(const std::string& line) = 0;
        virtual void parseNormals(const std::string& line) = 0;
        virtual void parseFaces(const std::string& line) = 0;
};
