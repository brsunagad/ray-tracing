#define _USE_MATH_DEFINES
#include <cmath>
#include <rt/solids/disc.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material)
{
    this->center = center;
    this->normal = normal;
    this->radius = radius;
}

BBox Disc::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const {
    float rdotn = dot(ray.d,normal);

    if (rdotn <= epsilon && rdotn >= -epsilon)
        return Intersection::failure();

    float distance = dot(center - ray.o, normal) / rdotn;
    Point intersectPoint = ray.getPoint(distance);
    float distToCenter = (intersectPoint - center).length();

    if (distToCenter < radius && distance >= 0 && distance < previousBestDistance) {
        return Intersection(distance, ray, this, normal, center);
    }
    else
        return Intersection::failure();
}

Solid::Sample Disc::sample() const {
    NOT_IMPLEMENTED;
}

float Disc::getArea() const {
    return M_PI * radius * radius;
}

}
