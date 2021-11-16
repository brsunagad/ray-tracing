#include <rt/solids/infiniteplane.h>

namespace rt {

InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material)
{
    this->origin = origin;
    this->normal = normal;
    this->material = material;
    this->texMapper = texMapper;
}

BBox InfinitePlane::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const {
    float ddotn = dot(ray.d,normal);
    
    if(ddotn == 0)
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
