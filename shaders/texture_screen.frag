#version 450 core
layout(location = 0) out vec4 FragColor;
layout(binding = 0, rgba8) uniform readonly image2D iTexture;
layout(binding = 1) uniform Input {
    vec2 iResolution;
};

void main() {
    FragColor = imageLoad(iTexture, ivec2(gl_FragCoord.xy));
}
