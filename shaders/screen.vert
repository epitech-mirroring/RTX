#version 450

layout(location = 0) in vec2 inPosition;
// Scene
struct Triangle {
    vec3 a;
    vec3 b;
    vec3 c;
    vec3 aNormal;
    vec3 bNormal;
    vec3 cNormal;
};

struct Material {
    vec3 color;
    vec3 emission;
    float emissionIntensity;
};

struct Mesh {
    uint startIdx;
    uint endIdx;
    vec3 boundingBoxMin;
    vec3 boundingBoxMax;
    mat4 transform;
    Material material;
};

struct Sphere {
    vec3 center;
    float radius;
};

layout(binding = 1) uniform Scene {
    uint iNumMeshes;
    uint iNumTriangles;
    uint iSceneChanged;
    uint iSkyboxEnabled;
};

layout(binding = 2) buffer Triangles {
    Triangle iTriangles[];
};

layout(binding = 3) buffer Meshes {
    Mesh iMeshes[];
};

void main() {
    gl_Position = vec4(inPosition, 0.0, 1.0);

    float trianglesPerVertex = iNumTriangles / 4.f;
    float startIdx = gl_VertexIndex * trianglesPerVertex;
    float endIdx = startIdx + trianglesPerVertex;
    bool last = gl_VertexIndex == 3;
    bool first = gl_VertexIndex == 0;
    if (last) {
        endIdx = iNumTriangles;
    }
    if (first) {
        startIdx = 0;
    }
    for (uint i = 0; i < iNumMeshes; i++) {
        Mesh mesh = iMeshes[i];
        vec3 boundingBoxMin = mesh.boundingBoxMin;
        vec3 boundingBoxMax = mesh.boundingBoxMax;
        bool hasRun = false;

        for (uint j = mesh.startIdx; j < mesh.endIdx; j++) {
            if (j < startIdx) {
                continue;
            }
            if (j >= endIdx) {
                break;
            }
            hasRun = true;
            Triangle triangle = iTriangles[j];
            vec3 a = (mesh.transform * vec4(triangle.a, 1.0)).xyz;
            vec3 b = (mesh.transform * vec4(triangle.b, 1.0)).xyz;
            vec3 c = (mesh.transform * vec4(triangle.c, 1.0)).xyz;
            vec3 aNormal = (mesh.transform * vec4(triangle.aNormal, 0.0)).xyz;
            vec3 bNormal = (mesh.transform * vec4(triangle.bNormal, 0.0)).xyz;
            vec3 cNormal = (mesh.transform * vec4(triangle.cNormal, 0.0)).xyz;

            vec3 normal = normalize(cross(b - a, c - a));

            if (dot(normal, aNormal) < 0.0) {
                vec3 temp = a;
                a = c;
                c = temp;
            }
            iTriangles[j] = Triangle(a, b, c, aNormal, bNormal, cNormal);

            boundingBoxMin = min(boundingBoxMin, min(a, min(b, c)));
            boundingBoxMax = max(boundingBoxMax, max(a, max(b, c)));
        }
        if (!hasRun) {
            continue;
        }
        iMeshes[i].boundingBoxMin = boundingBoxMin;
        iMeshes[i].boundingBoxMax = boundingBoxMax;
    }
}
