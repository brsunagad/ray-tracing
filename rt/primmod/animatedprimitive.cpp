#include <rt/primmod/animatedprimitive.h>

namespace rt {

AnimatedPrimitive::AnimatedPrimitive(Primitive* aniPrimitive, Vector transV):
    aniPrimitive(aniPrimitive), transV(transV)
{
    T = Matrix(Float4(1.f, 0.f, 0.f, transV.x), Float4(0.f, 1.f, 0.f, transV.y), Float4(0.f, 0.f, 1.f, transV.z), Float4(0.f, 0.f, 0.f, 1.f));
}

Primitive* AnimatedPrimitive::content() {
    return aniPrimitive;
}


void AnimatedPrimitive::changeMovement(const Vector& t) {
    transV = t;
    T = Matrix(Float4(1.f, 0.f, 0.f, t.x), Float4(0.f, 1.f, 0.f, t.y), Float4(0.f, 0.f, 1.f, t.z), Float4(0.f, 0.f, 0.f, 1.f));
}


Intersection AnimatedPrimitive::intersect(const Ray& ray, float previousBestDistance) const {
    // Random point in time of the translation:
    float dt = random();

    // std::cout << dt << std::endl;

    //Matrix for translation
    Matrix Tinv = Matrix(Float4(1.f, 0.f, 0.f, -transV.x*dt), Float4(0.f, 1.f, 0.f, -transV.y*dt), Float4(0.f, 0.f, 1.f, -transV.z*dt), Float4(0.f, 0.f, 0.f, 1.f));

    Ray rayInv = Ray(Tinv * ray.o, Tinv * ray.d);
    Intersection i = aniPrimitive->intersect(rayInv, previousBestDistance);
    //since we are not normalizing ray.d, we dont need to change previous best distance
    //ref: Fundamentals of CG 4th edition, Section 13.2 Instancing 
    if (i) {
        Vector normal = Tinv.transpose() * i.normal();
        Intersection intersection(i.distance , ray, i.solid, normal.normalize(), i.local());
        return intersection;
    } else
        return Intersection::failure();
}



void AnimatedPrimitive::setMaterial(Material* m) {
    aniPrimitive->setMaterial(m);
}

void AnimatedPrimitive::setCoordMapper(CoordMapper* cm) {
    aniPrimitive->setCoordMapper(cm);
}


BBox AnimatedPrimitive::getBounds() const {
    BBox archBBox = aniPrimitive->getBounds();
    Point p1(archBBox.min.x, archBBox.min.y, archBBox.min.z);
    Point p2(archBBox.max.x, archBBox.min.y, archBBox.min.z);
    Point p3(archBBox.min.x, archBBox.max.y, archBBox.min.z);
    Point p4(archBBox.min.x, archBBox.min.y, archBBox.max.z);
    Point p5(archBBox.min.x, archBBox.max.y, archBBox.max.z);
    Point p6(archBBox.max.x, archBBox.max.y, archBBox.min.z);
    Point p7(archBBox.max.x, archBBox.min.y, archBBox.max.z);
    Point p8(archBBox.max.x, archBBox.max.y, archBBox.max.z);
    Point p1T = T * p1;
    Point p2T = T * p2;
    Point p3T = T * p3;
    Point p4T = T * p4;
    Point p5T = T * p5;
    Point p6T = T * p6;
    Point p7T = T * p7;
    Point p8T = T * p8;
    float minx = min(
        min(p1T.x, p2T.x, p3T.x),
        min(p4T.x, p5T.x, p6T.x),
        min(p7T.x, p8T.x));
    float miny = min(
        min(p1T.y, p2T.y, p3T.y),
        min(p4T.y, p5T.y, p6T.y),
        min(p7T.y, p8T.y));
    float minz = min(
        min(p1T.z, p2T.z, p3T.z),
        min(p4T.z, p5T.z, p6T.z),
        min(p7T.z, p8T.z));
    float maxx = max(
        max(p1T.x, p2T.x, p3T.x),
        max(p4T.x, p5T.x, p6T.x),
        max(p7T.x, p8T.x));
    float maxy = max(
        max(p1T.y, p2T.y, p3T.y),
        max(p4T.y, p5T.y, p6T.y),
        max(p7T.y, p8T.y));
    float maxz = max(
        max(p1T.z, p2T.z, p3T.z),
        max(p4T.z, p5T.z, p6T.z),
        max(p7T.z, p8T.z));

    Point min(minx, miny, minz);
    Point max(maxx, maxy, maxz);
    return BBox(min, max);
}

}