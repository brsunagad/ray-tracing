#include <rt/intersection.h>

namespace rt {

Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& local)
{
    /* TODO */
}

Intersection::operator bool() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Intersection::failure() {
    /* TODO */ NOT_IMPLEMENTED;
}

Point Intersection::hitPoint() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Vector Intersection::normal() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Point Intersection::local() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
