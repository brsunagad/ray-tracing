#include <core/assert.h>
#include <core/macros.h>
#include <rt/ray.h>

namespace rt {

Ray::Ray(const Point& o, const Vector& d)
{
    this->o = o;
    this->d = d;
    assert(d != Vector::rep(0.0f));
}

Point Ray::getPoint(float distance) const {

    return Point(o + distance * d);
}

}
