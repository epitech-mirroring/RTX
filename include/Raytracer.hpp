/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef RTX_RAYTRACER_HPP
    #define RTX_RAYTRACER_HPP
    #include <string>

struct Arguments {
    std::string scenePath;
    std::string outputPath = "./screenshot.ppm";
    int width = 800;
    int height = 600;
    bool quit_after_render = true;
    bool disable_render_output = false;
    std::size_t frame_before_render = 30;
    bool quiet = false;
};

#endif // RTX_RAYTRACER_HPP
