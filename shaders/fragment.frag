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
};

RayHit hitSphere(Ray ray, Sphere sphere) {
    vec3 centeredRayOrigin = ray.origin - sphere.center;
    float a = dot(ray.direction, ray.direction);
    float b = 2.0 * dot(centeredRayOrigin, ray.direction);
    float c = dot(centeredRayOrigin, centeredRayOrigin) - sphere.radius * sphere.radius;

    float discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return RayHit(false, 0.0);
    }

    float hit1 = (-b - sqrt(discriminant)) / (2.0 * a);
    // float hit2 = (-b + sqrt(discriminant)) / (2.0 * a);
    return RayHit(true, hit1);
}

uniform float u_time;
uniform vec3 viewParams;
uniform vec3 cameraPosition;
uniform mat4 cameraLocalToWorldMatrix;

void main() {
    // Screen space (0 -> 0,5)
    vec2 p = gl_FragCoord.xy*2.0 - vec2(1920.0, 1080.0);
    gl_FragColor = vec4(p.x, p.y, 0.0, 1.0);

/*
    gl_FragColor = vec4(uv.x, uv.y, 0.0, 1.0);
    // View space (-1 -> 1)
    vec3 viewPointLocal = vec3(uv * 4.0 - 2.0, 1.0);
    // World space
    vec3 viewPointWorld = (cameraLocalToWorldMatrix * vec4(viewPointLocal, 1.0)).xyz;

    /*Ray ray;
    ray.origin = cameraPosition;
    ray.direction = normalize(viewPointWorld - cameraPosition);

    Sphere sphere;
    sphere.center = vec3(0.0, 0.0, 10.0);
    sphere.radius = 0.5;

    RayHit hit = hitSphere(ray, sphere);
    if (hit.hit) {
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    } else {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } */
}