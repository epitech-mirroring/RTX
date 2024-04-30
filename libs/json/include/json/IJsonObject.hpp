
/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <string>
#include <unordered_map>

class IJsonObject {
protected:
    static std::string cleanString(const std::string &string) {
        // Remove spaces, tabs, and newlines if not in a string
        std::string cleanedString;
        bool inString = false;
        for (const auto &c : string) {
            if (c == '"')
                inString = !inString;
            if (inString || (c != ' ' && c != '\t' && c != '\n'))
                cleanedString += c;
        }
        return cleanedString;
    }
public:
    virtual ~IJsonObject() = default;

    virtual std::string stringify() const = 0;

    virtual void parse(const std::string &string) = 0;

    virtual std::string getType() const = 0;

    virtual std::string getName() const = 0;
};
