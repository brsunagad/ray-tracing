#include <rt/intersection.h>

namespace rt {

Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& local):
    distance(distance),
    ray(ray),
    solid(solid),

    m_normal(normal),
    m_local(local)
{}

Intersection::operator bool() const {
    return success || this->solid != nullptr;
}

Intersection Intersection::failure() {
    Intersection fail = Intersection();
    fail.success = false;
    fail.solid = nullptr;
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
