#define _USE_MATH_DEFINES
#include <cmath>
#include <rt/solids/sphere.h>

namespace rt {

Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material): 
    center(center), 
    radius(radius), 
    Solid(texMapper, material) {}


BBox Sphere::getBounds() const {
    Point min(center.x - radius, center.y - radius, center.z - radius);
    Point max(center.x + radius, center.y + radius, center.z + radius);
    return BBox(min, max);
}

Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const {
	// We have to solve a cuadratic equation
    Vector vec_oc = ray.o - center;
    float a = dot(ray.d, ray.d);
    float b = 2*dot(ray.d,vec_oc);
    float c = dot(vec_oc, vec_oc) - (radius * radius);

    float calc_sqrt = (b * b) - (4 * a * c);

    // If the solution is imaginary, there are no intersections
    if (calc_sqrt < 0) return Intersection::failure();

    float sol_1 = (-b+sqrt(calc_sqrt))/(2*a);
    float sol_2 = (-b-sqrt(calc_sqrt))/(2*a);

    // We have to decide which distance is the correct one
    float distance = min(sol_1,sol_2);
    if (distance < 0){
    	// if the min is negative we use the other one
    	distance = max(sol_1,sol_2);
    	if (distance < 0)
    		//if it is also negative there are no hitpoints
    		return Intersection::failure();
    }
     

    if(distance >= 0 && distance<previousBestDistance){
    	Point hitpoint = ray.getPoint(distance);
        return Intersection(distance, ray, this, (hitpoint-center).normalize(), ray.getPoint(distance));;
    }
    else
        return Intersection::failure();
}

Solid::Sample Sphere::sample() const {
	NOT_IMPLEMENTED;
}

float Sphere::getArea() const {
    return 4 * M_PI*radius*radius;
}

}
