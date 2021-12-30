#include <rt/coordmappers/world.h>
#include <rt/intersection.h>

namespace rt {

Point WorldMapper::getCoords(const Intersection& hit) const {
    return Point(hit.local().x * scale.x, hit.local().y * scale.y, hit.local().z * scale.z);
}

WorldMapper::WorldMapper()
{
    scale = Vector::rep(1.0f);
}

WorldMapper::WorldMapper(const Vector& scale): scale(scale){}

}