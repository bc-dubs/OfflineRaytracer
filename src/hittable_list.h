#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>

class hittable_list : public hittable {
    public:
        std::vector<shared_ptr<hittable>> elements;

        hittable_list() {}
        hittable_list(shared_ptr<hittable> element) { add(element); }

        void clear(){ elements.clear(); }
        void add(shared_ptr<hittable> element) { elements.push_back(element); }
        bool hit(const ray& r, interval t_range, hit_record& rec) const override {
            hit_record temp_rec;
            bool has_hit = false;
            double closest_dist = t_range.max;

            for(const auto& elem : elements){
                if(elem->hit(r, interval(t_range.min, closest_dist), temp_rec)){
                    rec = temp_rec;
                    closest_dist = temp_rec.t;
                    has_hit = true;
                }
            }

            return has_hit;
        }
};

#endif