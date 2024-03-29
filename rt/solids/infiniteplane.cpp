#include <rt/solids/infiniteplane.h>

namespace rt {

InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material):
    origin(origin), 
    normal(normal), 
    Solid(texMapper, material) {}

BBox InfinitePlane::getBounds() const {
    return BBox::full();
}

Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const {
    float ddotn = dot(ray.d,normal);
    
    if(ddotn <= 1e-6 && ddotn >= -1e-6)
    	// if the ray is perpendicular to the normal, there would be none or infinite hitpoints
    	// both cases will return a failure.
        return Intersection::failure();


    float distance = dot(origin - ray.o, normal)/ddotn;
    if(distance >= 0 && distance<previousBestDistance){
    	// should we use origin or hitpoint for intersection?
    	return Intersection(distance,ray, this, normal, origin);
    }
    else
    	return Intersection::failure();
}

Solid::Sample InfinitePlane::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float InfinitePlane::getArea() const {
	// Infinite plane has to have infinite area
    return std::numeric_limits<float>::infinity();
}

}
