#include <rt/coordmappers/world.h>
#include <rt/intersection.h>

namespace rt {

Point WorldMapper::getCoords(const Intersection& hit) const {
    Point hitPoint = hit.hitPoint();
    return Point(scale.x * hitPoint.x, scale.y * hitPoint.y, scale.z * hitPoint.z);
}

WorldMapper::WorldMapper()
{
    scale = Vector::rep(1.0f);
}

WorldMapper::WorldMapper(const Vector& scale): scale(scale){}

}