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
    //reference https://iquilezles.org/www/articles/diskbbox/diskbbox.htm
    float x = radius * sqrt(1.0f - (normal.x * normal.x));
    float y = radius * sqrt(1.0f - (normal.y * normal.y));
    float z = radius * sqrt(1.0f - (normal.z * normal.z));
    Vector temp(x, y, z);
    return BBox(center - temp, center + temp);
}

Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const {
    float rdotn = dot(ray.d,normal);

    if (rdotn <= epsilon && rdotn >= -epsilon)
        return Intersection::failure();

    float distance = dot(center - ray.o, normal) / rdotn;
    Point intersectPoint = ray.getPoint(distance);
    float distToCenter = (intersectPoint - center).length();

    if (distToCenter < radius && distance >= 0 && distance < previousBestDistance) {
        return Intersection(distance, ray, this, normal, ray.getPoint(distance));
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
