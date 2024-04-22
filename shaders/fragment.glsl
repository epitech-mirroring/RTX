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

mat4 mul(mat4 a, vec4 b) {
    return mat4(
        a[0] * b.x,
        a[1] * b.y,
        a[2] * b.z,
        a[3] * b.w
    );
}

void main() {
    vec2 uv = gl_TexCoord[0].xy * 2.0 - 1.0;
    vec3 viewPointLocal = vec3(uv - 0.5, 1.0) * viewParams;
    mat4 temp = mul(cameraLocalToWorldMatrix, vec4(viewPointLocal, 1.0));
    vec3 viewPointWorld = vec3(temp[0].w, temp[1].w, temp[2].w);

    Ray ray;
    ray.origin = cameraPosition;
    ray.direction = normalize(viewPointWorld - ray.origin);

    gl_FragColor = vec4(uv.yyy, 1.0);
}