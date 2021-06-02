#include "vector3d.h"
#include <fmt/core.h>

int main()
{
    // There are two types of Vector: floating point and integer
    Vec3 vec_float(3.2);
    Vec3i vec_int(3);

    // Their features are the same so we will focus on Vec3
    // Constructor
    Vec3 vec0;              // vec0={0.0, 0.0 ,0.0}
    Vec3 vec1(5.7);         // vec1={5.7, 5.7, 5.7}
    Vec3 vec2(2.3, 3.6, 4.0);
    Vec3 vec3(vec2);        // vec3={2.3, 3.6, 4.0} (deep copy)

    // Assignment
    Vec3 vec4 = vec2;       // vec3={2.3, 3.6, 4.0}
    Vec3 vec5 = 5.0;        // vec4={5.0, 5.0, 5.0}

    // Access each element (3 ways)
    Vec3 vec_example(1.8, 0.4, 5.0);
    auto x = vec_example.x; // -> 1.8
    auto y = vec_example.y; // -> 0.4
    auto z = vec_example.z; // -> 5.0

    x = vec_example[0];     // -> 1.8
    y = vec_example[1];     // -> 0.4
    z = vec_example[2];     // -> 5.0

    x = vec_example.X;      // -> 1.8
    y = vec_example.Y;      // -> 0.4
    z = vec_example.Z;      // -> 5.0

    // Operation
    const Vec3 a(2);
    const Vec3 b(1, 2, 3);
    Vec3 c;

    c = a + b; // c={3, 4, 5}
    c = a - b; // c={1, 0, -1}
    c = a * b; // c={2, 4, 6}   (element-wise)
    c = a / b; // c={2, 1, 2/3} (element-wise)

    double k = 3;
    c = k * b; // c={3, 6, 9} (scalar * Vec3)
    c = b * k; // c={3, 6, 9} (Vec3 * scalar)
    c = b / k; // c={1/3, 2/3, 1}

    // Assignment Operation
    Vec3 d(2);

    d += Vec3(1, 2, 3); // d={3, 4, 5}
    d -= Vec3(1, 2, 3); // d={2, 2, 2}
    d *= 2;             // d={4, 4, 4}
    d *= Vec3(1, 2, 3); // d={4, 8, 12}
    d /= 2;             // d={2, 4, 6}
    d /= Vec3(1, 2, 3); // d={2, 2, 2}

    // Comparison
    bool p = Vec3(2)==Vec3(2,2,2); // true
    bool q = Vec3(3)==Vec3(2,3,4); // false

    // min & max element
    vec_example = Vec3(9.2, -0.2, 3.0);
    double min_elem = vec_example.min(); // -0.2
    double max_elem = vec_example.max(); // 9.2

    // norm
    vec_example = Vec3(0, 3, 4);
    double norm_square = vec_example.normSquare(); // 25
    double norm = vec_example.norm(); // 5

    // normalize
    Vec3 dir = vec_example.getNormalized(); // dir={0, 3/5, 4/5}            (vec_example is not normalized)
    vec_example.normalize();                // vec_example={0, 3/5, 4/5}    (now, vec_example is normalized)

    // dot
    Vec3 v1(1, 2, 3);
    Vec3 v2(2, 3, 4);
    double dot_prod = dot(v1, v2); // -> 2+6+12=20

    // cross
    v1 = Vec3(1, 0, 0);
    v2 = Vec3(0, 1, 0);
    Vec3 cross_prod = cross(v1, v2); // -> {0, 0, 1}

    // projection
    Vec3 v(3, 4, 5);
    Vec3 n(1, 0, 0); // the surface normal
    Vec3 projected = projectToPlane(v, n); // ->{0, 4, 5}

    // reflection
    Vec3 reflected = reflectVector(v, n); // ->{-3, 4, 5}

    // refraction
    int is_total_ref = 0;
    Vec3 refracted = refractVector(v, n, 1.0, 1.333, is_total_ref); // air to water refraction

    // print function
    std::string s = fmt::format("refracted vector is {}.", refracted);
    fmt::print("{}\n", s);
}