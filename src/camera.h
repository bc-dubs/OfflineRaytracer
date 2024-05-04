#ifndef CAMERA_H
#define CAMERA_H

#include "offlinert.h"
#include "hittable.h"

// Camera class sends rays into the world

class camera {
    public:
        // ====== FIELDS ======
        // These are set by the owning class rather than being set by a constructor

        // Image fields
        double aspect_ratio = 1.0;
        int image_width = 100;

        void render(const hittable& world){
            initialize();

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

                    color pixel_color = ray_color(r, world);
                    write_color(std::cout, pixel_color);
                }
                std::cout << "\n";
            }

            std::clog << "\n\rRender complete \n";
        }
    private:
        // ====== FIELDS ======
        // Image field
        int image_height;

        // Camera fields
        double focal_length = 1.0;
        double viewport_height = 2.0;
        double viewport_width;
        point3 camera_pos = point3(0, 0, 0);

        // Pixel fields
        // Worldspace vectors along the axes of the viewport
        vec3 viewport_u;
        vec3 viewport_v;
        // Worldspace vectors for traversing one pixel at a time
        vec3 delta_u;
        vec3 delta_v;
        // Worldspace positions for the top left of the viewport and the pixel grid
        point3 viewport_top_left;
        point3 pixel00_pos;

        void initialize(){
            // Calculate image height
            image_height = (int)(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            // Calculate viewport width
            viewport_width = viewport_height * ((double)image_width/image_height);

            // Calculate other viewport variables
            viewport_u = vec3(viewport_width, 0, 0);
            viewport_v = vec3(0, -viewport_height, 0);

            delta_u = viewport_u/image_width;
            delta_v = viewport_v/image_height;

            viewport_top_left = 
                camera_pos + focal_length * vec3(0, 0, -1) 
                - viewport_u / 2 
                - viewport_v / 2;
            pixel00_pos = viewport_top_left + delta_u / 2 + delta_v / 2;
        }

        color ray_color(const ray& r, const hittable& world){
            // OBJECTS
            hit_record rec;
            if(world.hit(r, interval(0, infinity), rec))
                return 0.5 * (rec.n_hat + color(1, 1, 1));

            // SKY
            vec3 unit_direction = normalize(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return color(0, 0, 1) * a + (1 - a) * color(1, 1, 1);
        }
};

#endif