/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/Json.hpp"
#include <criterion/criterion.h>
#include <fstream>
#include <cstdio>

Test(json_parser, empty_file)
{
    // Create an empty file
    std::ofstream file("tests/empty.json");
    file << "{}";
    file.close();

    // Parse the file
    JsonObject json = JsonObject::parseFile("tests/empty.json");
    // Check if the file is empty
    cr_assert_eq(json.getType(), "object");
    cr_assert_eq(json.getName(), "root");
    cr_assert_eq(json.stringify(), "{}");

    // Delete the file
    std::remove("tests/empty.json");
}

Test(json_parser, simple_file)
{
    // Create a simple file
    std::ofstream file("tests/simple.json");
    file << "{\"key\": \"value\"}";
    file.close();

    // Parse the file
    JsonObject json = JsonObject::parseFile("tests/simple.json");
    // Check if the file is correct
    cr_assert_eq(json.getType(), "object");
    cr_assert_eq(json.getName(), "root");

    // Get the first object
    auto *obj = json.getValue<JsonString>("key");
    cr_assert_eq(obj->getType(), "string");
    cr_assert_eq(obj->getName(), "key");
    cr_assert_eq(obj->getValue(), "value");

    // Delete the file
    std::remove("tests/simple.json");
}

Test(json_parser, simple_obj_all_types)
{
    // Create a simple file with all types
    std::ofstream file("tests/simple_obj_all_types.json");
    file << "{\"str\": \"value\", \"int\": 42, \"bool\": true, \"null\": null, \"float\": 42.42}";
    file.close();

    // Parse the file
    JsonObject json = JsonObject::parseFile("tests/simple_obj_all_types.json");
    // Check if the file is correct
    cr_assert_eq(json.getType(), "object");
    cr_assert_eq(json.getName(), "root");

    // String
    auto *str = json.getValue<JsonString>("str");
    cr_assert(str->getType() == "string");
    cr_assert_eq(str->getName(), "str");
    cr_assert_eq(str->getValue(), "value");

    // Int
    auto *num = json.getValue<JsonInt>("int");
    cr_assert_eq(num->getType(), "int");
    cr_assert_eq(num->getName(), "int");
    cr_assert_eq(num->getValue(), 42);

    // Bool
    auto *boolean = json.getValue<JsonBoolean>("bool");
    cr_assert_eq(boolean->getType(), "boolean");
    cr_assert_eq(boolean->getName(), "bool");
    cr_assert_eq(boolean->getValue(), true);

    // Null
    auto *null = json.getValue<JsonObject>("null");
    cr_assert_eq(null->getType(), "object");
    cr_assert_eq(null->getName(), "null");
    cr_assert_eq(null->isNull("null"), true);

    // Delete the file
    std::remove("tests/simple_obj_all_types.json");
}


Test(json_parser, object_in_object)
{
    // Create a file that contains an object in an object
    std::ofstream file("tests/object_in_object.json");
    file <<  "{\"key\": {\"key2\": \"value\"}}";
    file.close();

    // Parse the file
    JsonObject json = JsonObject::parseFile("tests/object_in_object.json");
    // Check if the file is correct
    cr_assert_eq(json.getType(), "object");

    // Get the first object
    auto *obj = json.getValue<JsonObject>("key");
    cr_assert_eq(obj->getType(), "object");
    cr_assert_eq(obj->getName(), "key");

    // Get the content of the object
    auto *inner_obj = obj->getValue<JsonString>("key2");
    cr_assert_eq(inner_obj->getType(), "string");
    cr_assert_eq(inner_obj->getName(), "key2");
    cr_assert_eq(inner_obj->getValue(), "value");

    // Delete the file
    std::remove("tests/object_in_object.json");
}

Test(json_parser, array_in_object) {
    // Create a file that contains an array in an object
    std::ofstream file("tests/array_in_object.json");
    file << "{\"key\": [\"value\", 42, true, null]}";
    file.close();

    // Parse the file
    JsonObject json = JsonObject::parseFile("tests/array_in_object.json");
    // Check if the file is correct
    cr_assert_eq(json.getType(), "object");

    // Get the array
    auto *arr = json.getValue<JsonArray>("key");
    cr_assert_eq(arr->getType(), "array");
    cr_assert_eq(arr->getName(), "key");
    cr_assert_eq(arr->size(), 4);

    // Get the first element
    auto *s = arr->getValue<JsonString>(0);
    cr_assert_eq(s->getType(), "string");
    cr_assert_eq(s->getName(), "0");
    cr_assert_eq(s->getValue(), "value");

    // Get the second element
    auto *i = arr->getValue<JsonInt>(1);
    cr_assert_eq(i->getType(), "int");
    cr_assert_eq(i->getName(), "1");
    cr_assert_eq(i->getValue(), 42);

    // Get the third element
    auto *b = arr->getValue<JsonBoolean>(2);
    cr_assert_eq(b->getType(), "boolean");
    cr_assert_eq(b->getName(), "2");
    cr_assert_eq(b->getValue(), true);

    // Get the fourth element
    auto *n = arr->getValue<JsonObject>(3);
    cr_assert_eq(n->getType(), "object");
    cr_assert_eq(n->getName(), "3");
    cr_assert_eq(n->isNull("null"), true);
    cr_assert_eq(arr->isNull(3), true);

    // Delete the file
    std::remove("tests/array_in_object.json");
}

Test(json_parser, json_obj_in_array)
{
    // Create a file that contains an object in an array
    std::ofstream file("tests/json_obj_in_array.json");
    file << "{\"array\": [{\"key\": \"value\"}]}";
    file.close();

    // Parse the file
    JsonObject json = JsonObject::parseFile("tests/json_obj_in_array.json");
    // Check if the file is correct
    cr_assert_eq(json.getType(), "object");
    cr_assert_eq(json.getName(), "root");

    // Get the array
    auto *arr = json.getValue<JsonArray>("array");
    cr_assert_eq(arr->getType(), "array");
    cr_assert_eq(arr->getName(), "array");
    cr_assert_eq(arr->size(), 1);

    // Get the first element
    auto *obj = arr->getValue<JsonObject>(0);
    cr_assert_eq(obj->getType(), "object");
    cr_assert_eq(obj->getName(), "0");

    // Get the content of the object
    auto *inner_obj = obj->getValue<JsonString>("key");
    cr_assert_eq(inner_obj->getType(), "string");
    cr_assert_eq(inner_obj->getName(), "key");
    cr_assert_eq(inner_obj->getValue(), "value");

    // Delete the file
    std::remove("tests/json_obj_in_array.json");
}

Test(json_parser, json_root_array)
{
    // Create a file that contains an array as root
    std::ofstream file("tests/json_root_array.json");
    file << "[\"value\", 42, true, null]";
    file.close();

    // Parse the file
    JsonArray json = JsonArray::parseFile("tests/json_root_array.json");
    // Check if the file is correct
    cr_assert_eq(json.getType(), "array");
    cr_assert_eq(json.getName(), "root");
    cr_assert_eq(json.size(), 4);

    // Get the first element
    auto *s = json.getValue<JsonString>(0);
    cr_assert_eq(s->getType(), "string");
    cr_assert_eq(s->getName(), "0");
    cr_assert_eq(s->getValue(), "value");

    // Get the second element
    auto * i = json.getValue<JsonInt>(1);
    cr_assert_eq(i->getType(), "int");
    cr_assert_eq(i->getName(), "1");
    cr_assert_eq(i->getValue(), 42);

    // Get the third element
    auto *b = json.getValue<JsonBoolean>(2);
    cr_assert_eq(b->getType(), "boolean");
    cr_assert_eq(b->getName(), "2");
    cr_assert_eq(b->getValue(), true);

    // Get the fourth element
    auto *n = json.getValue<JsonObject>(3);
    cr_assert_eq(n->getType(), "object");
    cr_assert_eq(n->getName(), "3");
    cr_assert_eq(n->isNull("null"), true);
    cr_assert_eq(json.isNull(3), true);

    // Delete the file
    std::remove("tests/json_root_array.json");
}

Test(json_parser, empty_root_array) {
    // Create a file that contains an empty array as root
    std::ofstream file("tests/empty_root_array.json");
    file << "[]";
    file.close();

    // Parse the file
    JsonArray json = JsonArray::parseFile("tests/empty_root_array.json");
    // Check if the file is correct
    cr_assert_eq(json.getType(), "array");
    cr_assert_eq(json.getName(), "root");
    cr_assert_eq(json.size(), 0);

    for (size_t i = 0; i < json.size(); i++) {
        cr_expect(false, "The array should be empty");
    }

    // Delete the file
    std::remove("tests/empty_root_array.json");
}

Test(json_parser, empty_array_in_object)
{
    // Create a file that contains an empty array in an object
    std::ofstream file("tests/empty_array_in_object.json");
    file << "{\"array\": []}";
    file.close();

    // Parse the file
    JsonObject json = JsonObject::parseFile("tests/empty_array_in_object.json");
    // Check if the file is correct
    cr_assert_eq(json.getType(), "object");
    cr_assert_eq(json.getName(), "root");

    // Get the array
    auto *arr = json.getValue<JsonArray>("array");
    cr_assert_eq(arr->getType(), "array");
    cr_assert_eq(arr->getName(), "array");
    cr_assert_eq(arr->size(), 0);

    // Delete the file
    std::remove("tests/empty_array_in_object.json");
}

Test(json_parser, empty_root_object) {
    // Create a file that contains an empty object as root
    std::ofstream file("tests/empty_root_object.json");
    file << "{}";
    file.close();

    // Parse the file
    JsonObject json = JsonObject::parseFile("tests/empty_root_object.json");
    // Check if the file is correct
    cr_assert_eq(json.getType(), "object");
    cr_assert_eq(json.getName(), "root");

    cr_assert_any_throw(json.getValue<JsonString>("key"));

    // Delete the file
    std::remove("tests/empty_root_object.json");
}
