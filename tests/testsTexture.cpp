/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include "Texture.hpp"

Test(Texture, Constructor)
{
    Texture texture = Texture();
    cr_assert_eq(texture.getPath(), "");
    cr_assert_eq(texture.getType(), Texture::NORMAL);
}

Test(Texture, Constructor2)
{
    Texture texture = Texture("path", Texture::DIFFUSE);
    cr_assert_eq(texture.getPath(), "path");
    cr_assert_eq(texture.getType(), Texture::DIFFUSE);
}

Test(Texture, Constructor3)
{
    Texture texture = Texture("path", Texture::DIFFUSE);
    Texture texture2 = Texture(texture);
    cr_assert_eq(texture2.getPath(), "path");
    cr_assert_eq(texture2.getType(), Texture::DIFFUSE);
}

Test(Texture, setPath)
{
    Texture texture = Texture();
    texture.setPath("path");
    cr_assert_eq(texture.getPath(), "path");
}

Test(Texture, setType)
{
    Texture texture = Texture();
    texture.setType(Texture::DIFFUSE);
    cr_assert_eq(texture.getType(), Texture::DIFFUSE);
}

Test(Texture, getPath)
{
    Texture texture = Texture("path", Texture::DIFFUSE);
    cr_assert_eq(texture.getPath(), "path");
}

Test(Texture, getType)
{
    Texture texture = Texture("path", Texture::DIFFUSE);
    cr_assert_eq(texture.getType(), Texture::DIFFUSE);
}
