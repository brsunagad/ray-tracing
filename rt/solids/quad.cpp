#include <rt/solids/quad.h>

namespace rt {

Quad::Quad(const Point& origin, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material):
    p1(origin),p2(origin+span1),p3(origin+span2),p4(origin+span1+span2),span1(span1),span2(span2)
{
    this->texMapper = texMapper;
    this->material = material;
    tri1 = new Triangle(p1, p2, p3, nullptr, nullptr);//quad can be split into two triangles
    tri2 = new Triangle(p3, p2, p4, nullptr, nullptr);
}

BBox Quad::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Quad::intersect(const Ray& ray, float previousBestDistance) const {
    //quad intersection can be determined by intersection with above two triangles
   Intersection quadIntersect = tri1->intersect(ray, previousBestDistance);
   if (quadIntersect)
       return Intersection(quadIntersect.distance,quadIntersect.ray, this, quadIntersect.normal(), p1);//replace p1 with bary centric coordinates in future assignments
   
   quadIntersect = tri2->intersect(ray, previousBestDistance);
   if (quadIntersect)
       return Intersection(quadIntersect.distance, quadIntersect.ray, this, quadIntersect.normal(), p1);

   return Intersection::failure();
}

Solid::Sample Quad::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Quad::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
