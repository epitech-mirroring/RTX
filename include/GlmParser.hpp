/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "json/Json.hpp"

class GlmParser {
public:
    static glm::vec3 parseVec3(JsonObject *obj);
    static glm::dquat parseQuat(JsonObject *obj);
    static glm::vec3 parseColor(JsonObject *obj);
};
