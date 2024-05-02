/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "GlmParser.hpp"

glm::vec3 GlmParser::parseVec3(JsonObject *obj)
{
    return {obj->getFloat("x"), obj->getFloat("y"), obj->getFloat("z")};
}

glm::dquat GlmParser::parseQuat(JsonObject *obj)
{
    return {obj->getFloat("x"), obj->getFloat("y"), obj->getFloat("z"), obj->getFloat("w")};
}

glm::vec3 GlmParser::parseColor(JsonObject *obj)
{
    return {obj->getFloat("r"), obj->getFloat("g"), obj->getFloat("b")};
}
