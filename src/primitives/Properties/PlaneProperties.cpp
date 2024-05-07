/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Properties/PlaneProperties.hpp"

PlaneProperties::PlaneProperties()
{
    _axes = glm::vec3(1.0f, 1.0f, 1.0f);
}

PlaneProperties::PlaneProperties(glm::vec3 axes)
{
    _axes = axes;
}

PlaneProperties::PlaneProperties(JsonObject *obj) {
    _axes.x = obj->getFloat("axes_x");
    _axes.y = obj->getFloat("axes_y");
    _axes.z = obj->getFloat("axes_z");
}

glm::vec3 &PlaneProperties::getAxes()
{
    return _axes;
}

glm::vec3 PlaneProperties::getAxes() const
{
    return _axes;
}

void PlaneProperties::setAxes(glm::vec3 axes)
{
    _axes = axes;
}
