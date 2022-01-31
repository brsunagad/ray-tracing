#include <rt/coordmappers/spherical.h>
#include <core/matrix.h>
#include <math.h>
namespace rt {

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef):
    origin(origin), zenith(zenith), azimuthRef(azimuthRef){}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    
    /*Vector normal = cross(azimuthRef, zenith).normalize();
    Vector azm = cross(zenith, normal).normalize();
    Matrix T = Matrix(Float4(azm), Float4(zenith.normalize()), Float4(normal), Float4(origin)).transpose().invert();
    Point transformed = T * hit.local();
    float phi = atan2f(transformed.z, transformed.x);
    float theta = atan2(transformed.y, sqrt(sqr(transformed.x) + sqr(transformed.z)));

    float u = phi / (2 * pi * azimuthRef.length());
    float v = theta / (zenith.length() * pi);

    return Point(u, v, 0);*/

    //solution corrected as per tutors instructions
    float xScale = azimuthRef.length();
    float yScale = zenith.length();

    Vector nZenith = zenith.normalize();
    Vector nAzimuth = azimuthRef.normalize();

    Vector pos = hit.local() - origin;
    Vector projection = pos - dot(pos, nZenith) * nZenith;

    float r = sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
    float theta = acosf(dot(pos.normalize(), nZenith));
    float phi = atan2(cross(projection, nAzimuth).length(), dot(projection, nAzimuth));//atan2(y/x)

    phi = dot(cross(projection, nAzimuth), nZenith) < 0 ? -phi : phi;
    return Point((phi / (2 * pi)) / xScale, (theta / pi) / yScale, 0);

    }

}