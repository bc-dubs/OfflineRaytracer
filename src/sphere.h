#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius) : center(center), radius(fmax(radius, 0)) {}

        bool hit(const ray& r, interval t_range, hit_record& rec) const override {
            vec3 origin_to_center = center - r.origin();
            auto a = r.direction().lengthSquared();
            auto h = dot(r.direction(), origin_to_center);
            auto c = origin_to_center.lengthSquared() - radius * radius;
            
            auto discr = h * h - a * c;
            if(discr < 0)
                return false;

            auto sqrtd = sqrt(discr);

            // Test the lower root
            auto root = (h - sqrtd) / a;
            if(!t_range.surrounds(root)){
                // If that fails, test the upper root
                root = (h + sqrtd) / a;
                if(!t_range.surrounds(root)){
                    return false; // If both fail, return false
                }
            }

            // Filling out passed-in parameter
            rec.t = root; // t = how far we had to proceed down the ray to hit the sphere
            rec.loc = r.at(root);
            rec.set_normal(r, (rec.loc - center) / radius);

            return true;
        }
    private:
        point3 center;
        double radius;
};

#endif