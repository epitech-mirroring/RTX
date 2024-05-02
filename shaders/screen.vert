#version 410 core
layout (location = 0) in vec3 aPos;
uniform vec2 iResolution;

void main() {
    gl_Position = vec4(aPos, 1.0);
}