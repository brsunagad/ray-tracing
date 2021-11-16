#include <rt/intersection.h>

namespace rt {

Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& local)
{
    this->distance = distance;
    this->ray = ray;
    this->solid = solid;

    this->m_normal = normal;
    this->m_local = local;
}

Intersection::operator bool() const {
    return success;
}

Intersection Intersection::failure() {
    Intersection fail = Intersection();
    fail.success = false;
    return fail;

}

Point Intersection::hitPoint() const {
    return ray.o + distance * ray.d;
}

Vector Intersection::normal() const {
    return m_normal;
}

Point Intersection::local() const {
    return m_local;
}

}
