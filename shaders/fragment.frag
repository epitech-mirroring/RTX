#version 120

struct Sphere {
    vec3 center;
    float radius;
};

struct Ray {
    vec3 origin;
    vec3 direction;
};

struct RayHit {
    bool hit;
    float distance;
    vec3 normal;
    vec3 position;
};

RayHit hitSphere(Ray ray, Sphere sphere) {
    RayHit hit;
    hit.hit = false;
    vec3 centeredRayOrigin = ray.origin - sphere.center;
    float a = dot(ray.direction, ray.direction);
    float b = 2.0 * dot(centeredRayOrigin, ray.direction);
    float c = dot(centeredRayOrigin, centeredRayOrigin) - sphere.radius * sphere.radius;

    float discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return hit;
    }
    hit.hit = true;
    hit.distance = (-b - sqrt(discriminant)) / (2.0 * a);
    hit.position = ray.origin + ray.direction * hit.distance;
    hit.normal = normalize(hit.position - sphere.center);
    // float hit2 = (-b + sqrt(discriminant)) / (2.0 * a);
    return hit;
}

uniform float u_time;
uniform vec3 viewParams;
uniform vec3 cameraPosition;
uniform mat4 cameraLocalToWorldMatrix;
uniform vec2 resolution;

void main() {
    // Screen space (0 -> 1)
    vec2 uv = gl_FragCoord.xy / vec2(resolution);
    // View space (-1 -> 1)
    vec3 viewPointLocal = vec3(uv - 0.5, 1.0) * viewParams;
    // World space
    vec3 viewPointWorld = (cameraLocalToWorldMatrix * vec4(viewPointLocal, 1.0)).xyz;

    Ray ray;
    ray.origin = cameraPosition;
    ray.direction = normalize(viewPointWorld - cameraPosition);
    gl_FragColor = vec4(ray.direction, 1.0);

    Sphere sphere;
    sphere.center = vec3(0.0, 0.0, 10.0);
    sphere.radius = 0.5;

    RayHit hit = hitSphere(ray, sphere);
    if (hit.hit) {
        gl_FragColor = vec4(hit.normal, 1.0);
    } else {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}