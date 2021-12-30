#include <rt/coordmappers/tmapper.h>

namespace rt {

TriangleMapper::TriangleMapper(Point ntv[3]): tv0(ntv[0]), tv1(ntv[1]), tv2(ntv[2]){}

TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2): tv0(tv0), tv1(tv1), tv2(tv2) {}

Point TriangleMapper::getCoords(const Intersection& hit) const {
    Float4 p = Float4(hit.local().x * tv0) + Float4(hit.local().y * tv1) + Float4(hit.local().z * tv2);
    return Point(p.x, p.y, p.z);
}

}