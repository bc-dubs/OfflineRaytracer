#ifndef HITTABLE_H
#define HITTABLE_H

class hit_record {
    public:
        point3 loc;
        vec3 n_hat;
        double t;
        bool is_front_face;

        /* Turns normal against viewing ray if it isn't already
            and records whether this is the object's front or back face*/
        void set_normal(const ray& r, const vec3& outward_normal) {
            is_front_face = dot(r.direction(), outward_normal) < 0;
            n_hat = is_front_face ? outward_normal : -outward_normal;
        }
};

class hittable {
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& r, interval t_range, hit_record& rec) const = 0;
};

#endif