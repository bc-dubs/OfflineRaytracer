#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"

using color = vec3;

inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return sqrt(linear_component);

    return 0;
}

void write_color(std::ostream& out, const color& pixel_color){
    auto red = pixel_color.r();
    auto green = pixel_color.g();
    auto blue = pixel_color.b();

    red = linear_to_gamma(red);
    green = linear_to_gamma(green);
    blue = linear_to_gamma(blue);

    static const interval intensity(0.0, 0.999);
    int r = int(256 * intensity.clamp(red));
    int g = int(256 * intensity.clamp(green));
    int b = int(256 * intensity.clamp(blue));

    out << r << ' ' << g << ' ' << b << ' ';
}

#endif