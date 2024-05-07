#version 450 core
// y+ is down
// x+ is right
// z+ is forward
// Output
layout(location = 0) out vec4 FragColor;
// View
layout(binding = 0) uniform View {
    vec2 iResolution;
    vec3 iViewPlaneParams;
    vec3 iCameraPosition;
    mat4 iCameraMatrix;
};
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
    Material material;
};
uint iNumSpheres;
Sphere iSpheres[50];

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


struct Ray {
    vec3 origin;
    vec3 direction;
};

struct Hit {
    bool hit;
    float distance;
    vec3 normal;
    vec3 position;
    Material material;
};

float randomValue(inout uint seed) {
    seed = seed * 747796405 + 2891336453;
    uint res = ((seed >> ((seed >> 28) + 4)) ^ seed) * 277803737;
    res = (res >> 22) ^ res;
    return res / 4294967295.0;
}

float randomNormalValue(inout uint seed) {
    float theta = 2.0 * 3.14159265359 * randomValue(seed);
    float rho = sqrt(-2.0 * log(randomValue(seed)));
    return rho * cos(theta);
}

vec3 randomDirection(inout uint seed) {
    float x = randomNormalValue(seed);
    float y = randomNormalValue(seed);
    float z = randomNormalValue(seed);
    return normalize(vec3(x, y, z));
}

bool isRayBoundingBoxIntersect(Ray ray, vec3 boxMin, vec3 boxMax)
{
    vec3 invDir = 1 / ray.direction;
    vec3 tMin = (boxMin - ray.origin) * invDir;
    vec3 tMax = (boxMax - ray.origin) * invDir;
    vec3 t1 = min(tMin, tMax);
    vec3 t2 = max(tMin, tMax);
    float tNear = max(max(t1.x, t1.y), t1.z);
    float tFar = min(min(t2.x, t2.y), t2.z);
    return tNear <= tFar;
}

Hit rayTriangle(Ray ray, Triangle tri)
{
    vec3 AB = tri.b - tri.a;
    vec3 AC = tri.c - tri.a;
    vec3 normal = cross(AB, AC);
    vec3 AO = ray.origin - tri.a;
    vec3 dirAO = cross(AO, ray.direction);

    float _determinant = -dot(ray.direction, normal);
    float invDet = 1 / _determinant;

    // Calculate dst to triangle & barycentric coordinates of intersection point
    float dst = dot(AO, normal) * invDet;
    float u = dot(AC, dirAO) * invDet;
    float v = -dot(AB, dirAO) * invDet;
    float w = 1 - u - v;

    // Initialize hit info
    Hit hit;
    hit.hit = _determinant >= 1E-6 && dst >= 0 && u >= 0 && v >= 0 && w >= 0;
    hit.position = ray.origin + ray.direction * dst;
    hit.normal = normalize(tri.aNormal * w + tri.bNormal * u + tri.cNormal * v);
    hit.distance = dst;
    return hit;
}

Hit raySphere(Ray ray, Sphere sphere)
{
    Hit hit;
    hit.hit = false;
    vec3 centeredRayOrigin = ray.origin - sphere.center;
    float a = dot(ray.direction, ray.direction);
    float b = 2.0 * dot(centeredRayOrigin, ray.direction);
    float c = dot(centeredRayOrigin, centeredRayOrigin) - sphere.radius * sphere.radius;

    float discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return hit;
    }
    float dist = (-b - sqrt(discriminant)) / (2.0 * a);
    if (dist < 0.0) {
        return hit;
    }

    hit.hit = true;
    hit.distance = dist;
    hit.position = ray.origin + ray.direction * hit.distance;
    hit.normal = normalize(hit.position - sphere.center);
    // float hit2 = (-b + sqrt(discriminant)) / (2.0 * a);
    return hit;
}

Hit computeHit(Ray ray) {
    Hit closestHit;
    closestHit.hit = false;
    closestHit.distance = 1E6;

    for (uint i = 0; i < iNumMeshes; i++) {
        Mesh mesh = iMeshes[i];
        if (!isRayBoundingBoxIntersect(ray, mesh.boundingBoxMin, mesh.boundingBoxMax)) {
            continue;
        }

        for (uint j = mesh.startIdx; j < mesh.endIdx; j++) {
            Triangle tri = iTriangles[j];
            Hit hit = rayTriangle(ray, tri);
            if (hit.hit && hit.distance < closestHit.distance) {
                closestHit = hit;
                closestHit.material = mesh.material;
                break;
            }
        }
    }
    for (uint i = 0; i < iNumSpheres; i++) {
        Sphere sphere = iSpheres[i];
        Hit hit = raySphere(ray, sphere);
        if (hit.hit && hit.distance < closestHit.distance) {
            closestHit = hit;
            closestHit.material = sphere.material;
        }
    }
    return closestHit;
}

vec3 lerp(vec3 a, vec3 b, float t) {
    return a * (1.0 - t) + b * t;
}

vec3 environmentLight(Ray ray) {
    // Horizon should be whitish, zenith should be blueish and ground should be dark (like brownish)
    vec3 horizonColor = vec3(1., 1., 1.);
    vec3 zenithColor = vec3(0.5, 0.7, 1.0);
    vec3 groundColor = vec3(0.2, 0.17, 0.1);
    vec3 sunDirection = normalize(vec3(0.5, 0.5, 0.5));
    float sunFocus = 1;
    float sunIntensity = 0.01;

    vec3 dir = vec3(ray.direction.x, -ray.direction.y, ray.direction.z);

    float skyGradientT = pow(smoothstep(0, 0.4, dir.y), 0.35);
    vec3 skyGradient = lerp(horizonColor, zenithColor, skyGradientT);
    float sun = pow(max(0, dot(dir, -sunDirection)), sunFocus) * sunIntensity;

    float groundToSkyT = smoothstep(-0.01, 0, dir.y);
    float sunMask = groundToSkyT >= 1.0 ? 0.0 : 1.0;
    return lerp(groundColor, skyGradient, groundToSkyT) + sun * sunMask;
}

vec3 raytrace(Ray ray, inout uint seed) {
    vec3 incomingLight = vec3(0.0, 0.0, 0.0);
    vec3 color = vec3(1.0, 1.0, 1.0);

    for (uint bounce = 0; bounce < 3; bounce++) {
        Hit hit = computeHit(ray);

        if (hit.hit) {
            ray.origin = hit.position;
            vec3 newDirection = randomDirection(seed);
            if (dot(newDirection, hit.normal) < 0.0) {
                newDirection = -newDirection;
            }
            ray.direction = newDirection;
            vec3 directLight = hit.material.emission * hit.material.emissionIntensity;
            incomingLight += directLight * color;
            color *= hit.material.color;
        } else {
            if (iSkyboxEnabled > 0) {
                incomingLight += environmentLight(ray) * color;
            }
            break;
        }
    }

    return incomingLight;
}

void main() {
    vec2 uv = gl_FragCoord.xy / iResolution.xy;

    vec3 viewPointLocal = vec3(uv - 0.5, 1.0) * iViewPlaneParams;
    vec3 viewPointWorld = (iCameraMatrix * vec4(viewPointLocal, 1.0)).xyz;
    uint seed = int(gl_FragCoord.x) + int(gl_FragCoord.y) * 1000;

    Ray ray;
    ray.origin = iCameraPosition;
    ray.direction = normalize(viewPointWorld - iCameraPosition);

    iNumSpheres = 0;

    vec3 incomingLight = vec3(0.0, 0.0, 0.0);
    uint numRaysPerPixel = 10;

    for (uint i = 0; i < numRaysPerPixel; i++) {
        incomingLight += raytrace(ray, seed);
    }

    FragColor = vec4(incomingLight / float(numRaysPerPixel), 1.0);
}
