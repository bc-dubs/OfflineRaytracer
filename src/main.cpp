// Ben Coukos-Wiley
// 4/2/24
// The core of the raytracer

#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>

double hit_sphere(const point3& center, double radius, const ray& r){
    vec3 origin_to_center = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), origin_to_center);
    auto c = dot(origin_to_center, origin_to_center) - radius * radius;
    auto discr = b * b - 4.0 * a * c;

    if(discr < 0)
        return -1.0;
    return (-b - sqrt(discr)) / (2.0 * a);
}

color ray_color(const ray& r){
    // t = how far we had to proceed down the ray to hit the sphere
    vec3 center = point3(0, 0, -1);
    double radius = 0.5;
    double t = hit_sphere(center, radius, r);
    if(t > 0){
        // Normalize vector btwn sphere center and intersection point
        vec3 n_hat = normalize(r.at(t) - center);
        return 0.5 * vec3(n_hat.x() + 1, n_hat.y() + 1, n_hat.z() + 1);
    }

    vec3 unit_direction = normalize(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return color(0, 0, 1) * a + (1 - a) * color(1, 1, 1);
}

int main(){
    // ======= IMAGE PROPERTIES =======
    // Initial parameters
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate image height
    int image_height = (int)(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // ======= CAMERA =======
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * ((double)image_width/image_height);
    auto camera_pos = point3(0, 0, 0);

    // Worldspace vectors along the axes of the viewport
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Worldspace vectors for traversing one pixel at a time
    vec3 delta_u = viewport_u/image_width;
    vec3 delta_v = viewport_v/image_height;

    // Worldspace positions for the top left of the viewport and the pixel grid
    point3 viewport_top_left = 
        camera_pos + focal_length * vec3(0, 0, -1) 
        - viewport_u / 2 
        - viewport_v / 2;
    point3 pixel00_pos = viewport_top_left + delta_u / 2 + delta_v / 2;

    // ======= RENDERING =======

    // Image header
    std::cout << "P3\n" << image_width << ' ' <<  image_height << " 255\n";

    // Image body
    for(int y = 0; y < image_height; y++){
        std::clog << "\rRows remaining:" << (image_height - y) << std::flush;
        for(int x = 0; x < image_width; x++){
            point3 cur_pixel_center = pixel00_pos + x * delta_u + y * delta_v;
            vec3 cur_ray_dir = cur_pixel_center - camera_pos;
            ray r(camera_pos, cur_ray_dir);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
        std::cout << "\n";
    }

    std::clog << "\n\rRender complete \n";
}