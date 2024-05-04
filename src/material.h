#ifndef MATERIAL_H
#define MATERIAL_H

#include "offlinert.h"

class hit_record;

class material {
    public:
        virtual ~material() = default;

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const {
            return false;
        }
};

class lambertian : public material {
    public:
        lambertian(const color& albedo) : albedo(albedo) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
        const override {
            auto scatter_direction = rec.n_hat + random_unit_vector();
            // Default to normal if offset made scatter direction almost zero
            scatter_direction = scatter_direction.is_near_zero()? rec.n_hat : scatter_direction;

            scattered = ray(rec.loc, scatter_direction);
            attenuation = albedo; // Huh??
            return true;
        }
    private:
        color albedo;
};

class metal : public material {
    public:
        metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1? fuzz : 1) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
        const override {
            vec3 reflect_direction = reflect(r_in.direction(), rec.n_hat);
            reflect_direction = normalize(reflect_direction) + (fuzz * random_unit_vector());
            scattered = ray(rec.loc, reflect_direction);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.n_hat) > 0.0); // Not 'scattered' in an exact sense but not absorbed for sure
        }
    private:
        color albedo;
        double fuzz;
};

#endif