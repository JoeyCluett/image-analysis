#pragma once

#include <map>
#include "core.h"

struct triangle_coords {

    xy_pair a,b,c;

};

float_t size(const triangle_coords& tri);

float_t size(const xy_pair& a, const xy_pair& b, const xy_pair& c);
