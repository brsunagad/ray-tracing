#include <rt/solids/triangle.h>

namespace rt {

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material)
{
    /* TODO */
}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material):
    v1(v1), v2(v2), v3(v3),v1v2(v2-v1), v1v3(v3-v1), normal(cross(v1v2, v1v3).normalize())
{
    this->material = material;
    this->texMapper = texMapper;
   
}

BBox Triangle::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const {
    //this implementation follows Möller-Trumbore algorithm 
  
    Vector pvec = cross(ray.d, v1v3);
    float det = dot(v1v2, pvec);

    if (det > -epsilon && det < epsilon)
        return Intersection::failure();   // This ray is parallel to this triangle.

    float invDet = 1.0 / det;
    Vector tvec = ray.o - v1;
    float u = invDet * dot(tvec, pvec);
    if (u < 0.0 || u > 1.0)
        return Intersection::failure();
    Vector qvec = cross(tvec, v1v2);
    float v = invDet * dot(ray.d, qvec);
    if (v < 0.0 || u + v > 1.0)
        return Intersection::failure();

    float t = invDet * dot(v1v3, qvec);
    if ((t > epsilon) && (t < previousBestDistance))
        return Intersection(t, ray, this, normal, getBaryCentricCoordinates(ray.getPoint(t)));
    else
        return  Intersection::failure();
   
}

Point Triangle::getBaryCentricCoordinates(const Point& p) const {
    Point temp;
    temp.x = 0.5 * cross(v2 - p, v3 - p).length() / getArea();
    temp.y = 0.5 * cross(v1 - p, v3 - p).length() / getArea();
    temp.z = 0.5 * cross(v1 - p, v2 - p).length() / getArea();
   
    return temp;
}


Solid::Sample Triangle::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Triangle::getArea() const {
    return 0.5 * cross(v2-v1,v3-v1).length();
}

}