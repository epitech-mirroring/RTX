/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/Properties/PropertiesFactory.hpp"

AbstractProperties *PropertiesFactory::createProperties(const std::string &type, JsonObject *obj)
{
    if (_creators.find(type) == _creators.end())
        throw std::runtime_error("Unknown properties type: " + type);
    return _creators[type](obj);
}

void PropertiesFactory::registerProperties(const std::string &type, std::function<AbstractProperties *(JsonObject *)> creator)
{
    _creators[type] = std::move(creator);
}
