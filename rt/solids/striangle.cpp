#include <rt/solids/striangle.h>
#include <rt/intersection.h>
#include <core/interpolate.h>

namespace rt {

SmoothTriangle::SmoothTriangle(Point vertices[3], Vector normals[3], CoordMapper* texMapper, Material* material):
    Triangle(vertices[0], vertices[1], vertices[2], texMapper, material), n1(normals[0]), n2(normals[1]), n3(normals[2])
{
}

SmoothTriangle::SmoothTriangle(const Point& v1, const Point& v2, const Point& v3, const Vector& n1, const Vector& n2, const Vector& n3, CoordMapper* texMapper, Material* material):
    Triangle(v1, v2, v3, texMapper, material), n1(n1), n2(n2), n3(n3) {}

Intersection SmoothTriangle::intersect(const Ray& ray, float previousBestDistance) const {
    Intersection i = Triangle::intersect(ray, previousBestDistance);
    if (i) {
        Vector normal = lerpbar(n1, n2, n3, i.local().x, i.local().y).normalize();
        return Intersection(i.distance, i.ray, this, normal, i.local());
    }
    else
        return Intersection::failure();
}

}