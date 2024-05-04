// Ben Coukos-Wiley
// 4/2/24
// The core of the raytracer

#include "offlinert.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

int main(){
    // ======= IMAGE PROPERTIES =======
    // Initial parameters
    

    

    // ======= WORLD =======
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100)); // Ground

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    
    cam.render(world);
}