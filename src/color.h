#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color){
    auto red = pixel_color.r();
    auto green = pixel_color.g();
    auto blue = pixel_color.b();

    static const interval intensity(0.0, 0.999);
    int r = int(256 * intensity.clamp(red));
    int g = int(256 * intensity.clamp(green));
    int b = int(256 * intensity.clamp(blue));

    out << r << ' ' << g << ' ' << b << ' ';
}

#endif