/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <cstddef>
#include "primitives/Properties/AbstractProperties.hpp"
#include "json/Json.hpp"

class CubeProperties : public AbstractProperties {
public:
    CubeProperties() : AbstractProperties() { _size = 1; };
    explicit CubeProperties(std::size_t size) : AbstractProperties() { _size = size; };
    explicit CubeProperties(JsonObject *obj) : AbstractProperties(obj) { _size = obj->getInt("size");};
    ~CubeProperties() override = default;
    [[nodiscard]] std::size_t getSize() const { return _size; }
    [[nodiscard]] std::size_t &getSize() { return _size; }
    void setSize(std::size_t size) { _size = size; }
protected:
    std::size_t _size;
};
