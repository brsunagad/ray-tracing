#include <rt/solids/sphere.h>

namespace rt {

Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material)
{
    this->center = center;
    this->radius = radius;
    this->material = material;
    this->texMapper = texMapper;
}

BBox Sphere::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const {
    float distance;
    return Intersection::failure();
}

Solid::Sample Sphere::sample() const {
	NOT_IMPLEMENTED;
}

float Sphere::getArea() const {
    return 4 * M_PI*radius*radius;
}

}
