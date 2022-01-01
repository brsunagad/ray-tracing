#include <rt/solids/quad.h>

namespace rt {

Quad::Quad(const Point& origin, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material):
    p1(origin),p2(origin+span1),p3(origin+span2),p4(origin+span1+span2),span1(span1),span2(span2), Solid(texMapper, material) 
{

    tri1 = new Triangle(p1, p2, p3, nullptr, nullptr);//quad can be split into two triangles
    tri2 = new Triangle(p3, p2, p4, nullptr, nullptr);
}

BBox Quad::getBounds() const {
    Point min, max;
    min.x = rt::min(rt::min(p1.x, p2.x, p3.x), p4.x);
    min.y = rt::min(rt::min(p1.y, p2.y, p3.y), p4.y);
    min.z = rt::min(rt::min(p1.z, p2.z, p3.z), p4.z);

    max.x = rt::max(rt::max(p1.x, p2.x, p3.x), p4.x);
    max.y = rt::max(rt::max(p1.y, p2.y, p3.y), p4.y);
    max.z = rt::max(rt::max(p1.z, p2.z, p3.z), p4.z);

    return BBox(min, max);
}

Intersection Quad::intersect(const Ray& ray, float previousBestDistance) const {
    //quad intersection can be determined by intersection with above two triangles
   Intersection quadIntersect = tri1->intersect(ray, previousBestDistance);
   if (quadIntersect)
       return Intersection(quadIntersect.distance,quadIntersect.ray, this, quadIntersect.normal(), getBaryCoords(quadIntersect.hitPoint()));//replace p1 with bary centric coordinates in future assignments
   
   quadIntersect = tri2->intersect(ray, previousBestDistance);
   if (quadIntersect)
       return Intersection(quadIntersect.distance, quadIntersect.ray, this, quadIntersect.normal(), getBaryCoords(quadIntersect.hitPoint()));

   return Intersection::failure();
}

Solid::Sample Quad::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Quad::getArea() const {
    return tri1->getArea()+tri2->getArea();
}

Point Quad::getBaryCoords(const Point& p) const {

    Vector op = p - p1;
    float u =  0.f, v = 0.f;
    if (span1.z * span2.y != 0.0f || span2.z * span1.y != 0.0f) {
        u = (op.z * span2.y - op.y * span2.z) / (span1.z * span2.y - span1.y * span2.z);
        v = (op.z * span1.y - op.y * span1.z) / (span2.z * span1.y - span2.y * span1.z);
    }
    else if (span1.x * span2.y != 0.0f || span1.y * span2.x != 0.0f) {
        u = (op.x * span2.y - op.y * span2.x) / (span1.x * span2.y - span1.y * span2.x);
        v = (op.x * span1.y - op.y * span1.x) / (span2.x * span1.y - span2.y * span1.x);
    }
    else if (span1.z * span2.x != 0.0f || span1.x * span2.z != 0.0f) {
        u = (op.z * span2.x - op.x * span2.z) / (span1.z * span2.x - span1.x * span2.z);
        v = (op.z * span1.x - op.x * span1.z) / (span2.z * span1.x - span2.x * span1.z);

    }
    Point bary(u, v, 0.0f);
    return bary;
}
}
