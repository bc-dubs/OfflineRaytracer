#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color){
    auto red = pixel_color.r();
    auto green = pixel_color.g();
    auto blue = pixel_color.b();

    int r = int(255.999 * red);
    int g = int(255.999 * green);
    int b = int(255.999 * blue);

    out << r << ' ' << g << ' ' << b << ' ';
}

#endif