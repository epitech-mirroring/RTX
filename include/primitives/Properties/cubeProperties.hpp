/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "primitives/Properties/abstractProperties.hpp"
#include <cstddef>

class cubeProperties : public abstractProperties {
    public:
        cubeProperties() = default;
        explicit cubeProperties(std::size_t size) : _size(size) {};
        explicit cubeProperties(JsonObject *obj) { _size = obj->getInt("size");};
        ~cubeProperties() = default;
        [[nodiscard]] std::size_t getSize() const { return _size; }
        [[nodiscard]] std::size_t &getSize() { return _size; }
        void setSize(std::size_t size) { _size = size; }
    protected:
        std::size_t _size;
};
