#include <rt/coordmappers/cylindrical.h>
#include <core/matrix.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis):
    origin(origin), longitudinalAxis(longitudinalAxis), polarAxis(polarAxis){}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
    //corrections as per tutors instruction
    float xScale = polarAxis.length();
    float yScale = longitudinalAxis.length();

    Vector nPolar = polarAxis.normalize();
    Vector nLong = longitudinalAxis.normalize();

    Vector pos = hit.local() - origin;
    Vector projection = pos - dot(pos, nLong) * nLong;

    float r = sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
    float y = dot(pos, nLong);
    float theta = atan2(cross(projection, nPolar).length(), dot(projection, nPolar));//atan2(y/x)

    theta = dot(cross(projection, nPolar), nLong) < 0 ? -theta : theta;
    return Point((theta / (2 * pi)) / xScale, (theta / pi) / yScale, r);

    /*Vector normal = -cross(polarAxis, longitudinalAxis).normalize();
    Vector azm = cross(normal, longitudinalAxis).normalize();
    Matrix T = Matrix(Float4(azm), Float4(normal), Float4(longitudinalAxis), Float4(origin)).transpose().invert();
    Point transformed = T * hit.local();
    float phi = atan2f(transformed.y, transformed.x);
    
    float u = phi / (2 * pi * polarAxis.length());
    float v = transformed.z/ (longitudinalAxis.length() * pi);
    return Point(u, v, 0);*/
   
    /*Vector normal = cross(polarAxis, longitudinalAxis).normalize();
    Vector newPolar = cross(longitudinalAxis, normal);
    Matrix T = Matrix(Float4(newPolar), Float4(longitudinalAxis), Float4(normal), Float4(origin)).transpose().invert();
    Point transformed = T * hit.local();
    float phi = atan2f(-transformed.z, transformed.x);

    float u = phi / (2 * pi * polarAxis.length());
    float v = transformed.y / (longitudinalAxis.length() * pi);
    return Point(u, v, 0);*/
}

}