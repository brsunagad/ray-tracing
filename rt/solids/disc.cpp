#define _USE_MATH_DEFINES
#include <cmath>
#include <rt/solids/disc.h>
#include <core/random.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material): 
    center ( center),
    normal ( normal),
    radius  (radius),
    Solid(texMapper, material){}

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
    float theta = random();
    float v = radius * sqrt(random());
    float r1 = v * cos(2 * pi * theta);
    float r2 = v * sin(2 * pi * theta);
    float r3 = v * sin(2 * pi * theta);

    Sample sample;
    sample.point = Point(r1 + center.x , r2 + center.y, r3 + center.z);
    sample.normal = normal;
    return sample;
}

float Disc::getArea() const {
    return M_PI * radius * radius;
}

}
