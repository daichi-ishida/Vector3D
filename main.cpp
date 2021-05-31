#include "vector3d.h"
#include <fmt/core.h>

int main()
{
    Vec3 v(1, 2, 2);
    Vec3 v2(1, 0, 0);

    Vec3 x = reflectVector(v, v2);
    std::string s = fmt::format("Vec3 is {}.", x);
    fmt::print("{}\n", s);
}