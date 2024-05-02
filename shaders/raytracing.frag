#version 430
out vec4 FragColor;
uniform vec2 iResolution;
uniform vec3 iViewPlaneParams;
uniform vec3 iCameraPosition;
uniform mat4 iCameraMatrix;

struct Triangle {
    vec3 a;
    vec3 b;
    vec3 c;
    vec3 aNormal;
    vec3 bNormal;
    vec3 cNormal;
};

struct Sphere {
    vec3 center;
    float radius;
};

struct Mesh {
    uint startIdx;
    uint endIdx;
    vec3 boundingBoxMin;
    vec3 boundingBoxMax;
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
};

uniform uint iNumTriangles;
uniform uint iNumMeshes;
layout(binding = 1) readonly buffer Triangles {
    Triangle iTriangles[];
};
layout(binding = 2) readonly buffer Meshes {
    Mesh iMeshes[];
};

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

Hit RayTriangle(Ray ray, Triangle tri)
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

Hit hitSphere(Ray ray, Sphere sphere) {
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

Hit ComputeHit(Ray ray) {
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
            Hit hit = RayTriangle(ray, tri);
            if (hit.hit && hit.distance < closestHit.distance) {
                closestHit = hit;
                break;
            }
        }
    }
    return closestHit;
}

vec3 Raytrace(Ray ray) {
    bool hasHit = false;

    for (uint bounce = 0; bounce < 10; bounce++) {
        Hit hit = ComputeHit(ray);

        if (hit.hit) {
            ray.origin = hit.position;
            ray.direction = reflect(ray.direction, hit.normal);
            hasHit = true;
        } else {
            break;
        }
    }
    return hasHit ? vec3(1.0, 0.0, 0.0) : vec3(0.0, 0.0, 0.0);
}

void main() {
    vec2 uv = gl_FragCoord.xy / iResolution.xy;

    vec3 viewPointLocal = vec3(uv - 0.5, 1.0) * iViewPlaneParams;
    vec3 viewPointWorld = (iCameraMatrix * vec4(viewPointLocal, 1.0)).xyz;

    Ray ray;
    ray.origin = iCameraPosition;
    ray.direction = normalize(viewPointWorld - iCameraPosition);

    FragColor = vec4(iMeshes[0].boundingBoxMax, 1.0);
    /*
    Hit hit = ComputeHit(ray);
    FragColor = hit.hit ? vec4(1.0, 0.0, 0.0, 1.0) : vec4(0.0, 0.0, 0.0, 1.0);*/
}
