#include <rt/coordmappers/spherical.h>
#include <core/matrix.h>
namespace rt {

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef):
    origin(origin), zenith(zenith), azimuthRef(azimuthRef){}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    /*Vector hitVector = hit.local() - origin;
    float v = acos(dot(zenith.normalize(), hitVector.normalize()));
    
    //calculate perpendicular polar axis
    Vector newAzimuthRef = (azimuthRef - dot(zenith.normalize(), azimuthRef) * zenith);

    //Project hitVector 
    Vector projHit = (hitVector - dot(zenith.normalize(), hitVector) * zenith).normalize();
    float u = acos(dot(projHit, newAzimuthRef));
    return Point(u, v, 0);*/

    /*Vector normal = -cross(azimuthRef, zenith).normalize();
    Vector azm = cross(normal, zenith).normalize();
    Matrix T = Matrix(Float4(azm), Float4(normal), Float4(zenith.normalize()), Float4(origin)).transpose().invert();
    Point transformed = T * hit.local();
    float phi = atan2f(transformed.y, transformed.x);
    float theta = atan2(transformed.z, sqrt(sqr(transformed.x) + sqr(transformed.y)));

    float u =  phi / (2 * pi * azimuthRef.length());
    float v =  theta / (zenith.length() * pi);
    return Point(u, v, 0);*/

    
    Vector normal = cross(azimuthRef, zenith).normalize();
    Vector azm = cross(zenith, normal).normalize();
    Matrix T = Matrix(Float4(azm), Float4(zenith.normalize()), Float4(normal), Float4(origin)).transpose().invert();
    Point transformed = T * hit.local();
    float phi = atan2f(transformed.z, transformed.x);
    float theta = atan2(transformed.y, sqrt(sqr(transformed.x) + sqr(transformed.z)));

    float u = phi / (2 * pi * azimuthRef.length());
    float v = theta / (zenith.length() * pi);
    return Point(u, v, 0);
}

}