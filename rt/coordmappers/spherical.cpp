#include <rt/coordmappers/spherical.h>

namespace rt {

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef):
    origin(origin), zenith(zenith), azimuthRef(azimuthRef){}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    Vector hitVector = hit.local() - origin;
    float v = acos(dot(zenith.normalize(), hitVector.normalize()));

    //calculate perpendicular polar axis
    Vector newAzimuthRef = (azimuthRef - dot(zenith.normalize(), azimuthRef) * zenith);

    //Project hitVector 
    Vector projHit = (hitVector - dot(zenith.normalize(), hitVector) * zenith).normalize();
    float u = acos(dot(projHit, newAzimuthRef));
    return Point(u, v, 0);
}

}