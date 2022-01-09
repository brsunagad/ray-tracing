#include <rt/coordmappers/cylindrical.h>
#include <core/matrix.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis):
    origin(origin), longitudinalAxis(longitudinalAxis), polarAxis(polarAxis){}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
    Vector hitVector = hit.local() - origin;
    float v = dot(longitudinalAxis.normalize(), hitVector) / longitudinalAxis.length();
    
    //calculate perpendicular polar axis
    Vector newPolar = (polarAxis - dot(longitudinalAxis.normalize(), polarAxis) * longitudinalAxis);

    //Project hitVector 
    Vector projHit = (hitVector - v * longitudinalAxis).normalize();
    float u = acos(dot(projHit, newPolar));
    return Point(u, v, 0);

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