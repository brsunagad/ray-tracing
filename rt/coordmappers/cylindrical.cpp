#include <rt/coordmappers/cylindrical.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis):
    origin(origin), longitudinalAxis(longitudinalAxis), polarAxis(polarAxis){}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
    Vector hitVector = hit.local() - origin;
    float v = dot(longitudinalAxis.normalize(), hitVector) / longitudinalAxis.length();

    //calculate perpendicular polar axis
    Vector newPolar = (polarAxis - dot(longitudinalAxis.normalize(), polarAxis) * longitudinalAxis.normalize());

    //Project hitVector 
    Vector projHit = (hitVector - v * longitudinalAxis).normalize();
    float u = acos(dot(projHit, newPolar));
    return Point(u, v, 0);
}

}