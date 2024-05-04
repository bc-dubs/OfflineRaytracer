#ifndef VEC3_H
#define VEC3_H

class vec3 {
    public:
        // The elements of this vector
        double e[3];

        // Constructors
        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        // Getters for each element (read-only!)
        double x() const {return e[0]; }
        double y() const {return e[1]; }
        double z() const {return e[2]; }

        double r() const {return e[0]; }
        double g() const {return e[1]; }
        double b() const {return e[2]; }

        // Operators
        vec3 operator-() const { return vec3(-x(), -y(), -z()); }
        double operator[](int i) const { return e[i]; } // Read-only overload used on RHS of assignment
        double& operator[](int i) { return e[i]; } // Read-write overload used on LHS of assignment

        vec3& operator+=(const vec3& other) {
            e[0] += other.x();
            e[1] += other.y();
            e[2] += other.z();
            return *this; // Dereferenced 'this' pointer returns copy of data
        };

        vec3& operator*=(double scalar) {
            e[0] *= scalar;
            e[1] *= scalar;
            e[2] *= scalar;
            return *this; // Dereferenced 'this' pointer returns copy of data
        };

        vec3& operator/=(double scalar) {
            return *this *= 1/scalar; // not actually a copy of the data, lvalue shenanigans??
        };

        // Functions
        double length() const { // const = does not edit any part of its enclosing object
            return sqrt(lengthSquared());
        }

        double lengthSquared() const {
            return x() * x() + y() * y() + z() * z();
        }

        bool is_near_zero() const {
            // Are all 3 coordinates very close to zero?
            auto s = 1e-8; // Very small number
            return (fabs(x()) < s) && (fabs(y()) < s) && (fabs(z()) < s);
        }

        static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        static vec3 random(double min, double max) {
            return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
        }
};

using point3 = vec3; // Alias

// Vector functions and operators

// 'inline' = substitute this function for its reference during compiling
inline std::ostream& operator<<(std::ostream& out, const vec3& v){ // Passes in reference to output stream
    return out << "<" << v.x() << " " << v.y() << " " << v.z() << ">";
}

inline vec3 operator+(const vec3& u, const vec3& v) 
{
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator-(const vec3& u, const vec3& v) 
{
    return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline vec3 operator*(const vec3& v, double scalar) 
{
    return vec3(v.x()*scalar, v.y()*scalar, v.z()*scalar);
}

inline vec3 operator*(const vec3& u, const vec3& v) // Not real vector multiplication
{
    return vec3(u.x()*v.x(), u.y()*v.y(), u.z()*v.z());
}

inline vec3 operator*(double scalar, const vec3& v) 
{
    return v * scalar;
}

inline vec3 operator/(const vec3& v, double scalar) 
{
    return vec3(v.x()/scalar, v.y()/scalar, v.z()/scalar);
}

inline double dot(const vec3& u, const vec3& v){
    return u.x()*v.x() + u.y()*v.y() + u.z()*v.z();
}

inline vec3 cross(const vec3& u, const vec3& v){
    return vec3(
        u.y()*v.z() - u.z()*v.y(),
        u.z()*v.x() - u.x()*v.z(),
        u.x()*v.y() - u.y()*v.x());
}

inline vec3 normalize(const vec3& v){
    return v / v.length();
}
inline vec3 random_unit_vector(){
    // Using spherical coordinates
    double theta = 2 * pi * random_double();
    double phi = 2 * pi * random_double();

    return vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
}
/*
inline vec3 random_unit_vector() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.lengthSquared() < 1)
            return normalize(p);
    }
}*/

inline vec3 random_on_hemisphere(const vec3& n){
    vec3 v = random_unit_vector();
    v = (dot(v, n) < 0)? -v : v;
    return v;
}

inline vec3 reflect(const vec3& v, const vec3& n){
    return v - 2*dot(v,n)*n;
}

#endif