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
        int samples_per_pixel = 10;
        int max_recursion_depth = 10;

        void render(const hittable& world){
            initialize();

            // ======= RENDERING =======

            // Image header
            std::cout << "P3\n" << image_width << ' ' <<  image_height << " 255\n";

            // Image body
            for(int y = 0; y < image_height; y++){
                std::clog << "\rRows remaining: " << (image_height - y) << std::flush;
                for(int x = 0; x < image_width; x++){
                    color pixel_color(0, 0, 0);
                    for(int s = 0; s < samples_per_pixel; s++){
                        pixel_color += sample_partition * ray_color(get_ray(x, y), max_recursion_depth, world);
                    }
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
        // How much of the total color each ray should contribute
        double sample_partition;

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

            sample_partition = 1.0/samples_per_pixel;
        }

        ray get_ray(int x, int y) const{
            vec3 offset = sample_square();

            point3 pixel_sample = pixel00_pos 
                + (x + offset.x()) * delta_u 
                + (y + offset.y()) * delta_v;

            vec3 ray_dir = pixel_sample - camera_pos;
            return ray(camera_pos, ray_dir);
        }

        vec3 sample_square() const{
            return vec3(random_double(), random_double(), 0) - vec3(0.5, 0.5, 0);
        }

        color ray_color(const ray& r, int depth, const hittable& world){
            // CHECK MAX RECURSION
            if(depth <= 0)
                return color(1, 1, 1);

            // OBJECTS
            hit_record rec;
            if(world.hit(r, interval(0.001, infinity), rec)){
                vec3 diffuse_direction = rec.n_hat + random_unit_vector();
                return 0.5 * ray_color(ray(rec.loc, diffuse_direction), depth-1, world);
            }

            // SKY
            vec3 unit_direction = normalize(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return color(0, 0, 1) * a + (1 - a) * color(1, 1, 1);
        }
};

#endif