// triangle helper library

#include "core.h"
#include "triangles.h"

// evaluate the size of a triangle based on its coordinates
float_t size(const triangle_coords& tri) {

    const auto& a = tri.a;
    const auto& b = tri.b;
    const auto& c = tri.c;

    auto sz = (a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y)) / 2.0;

    return (sz < 0) ? -sz : sz; // quick abs()
}

float_t size(const xy_pair& a, const xy_pair& b, const xy_pair& c) {

    auto sz = (a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y)) / 2.0;
    
    return (sz < 0) ? -sz : sz; // quick abs()
}
