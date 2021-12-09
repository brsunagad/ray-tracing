#include <rt/primmod/instance.h>

namespace rt {

Instance::Instance(Primitive* content)
{
    archetype = content;
    T = Matrix::identity();
    Tinv = Matrix::identity();
}

Primitive* Instance::content() {
    return archetype;
}

void Instance::reset() {
    T = Matrix::identity();
    Tinv = Matrix::identity();
}

void Instance::translate(const Vector& t) {
    Matrix translation = Matrix(Float4(1.f, 0.f, 0.f, t.x), Float4(0.f, 1.f, 0.f, t.y), Float4(0.f, 0.f, 1.f, t.z), Float4(0.f, 0.f, 0.f, 1.f));
    T = product(translation, T);
    Tinv = T.invert();
}

void Instance::rotate(const Vector& nnaxis, float angle) {
    Vector r = nnaxis.normalize();

    Vector s;
    if (r.x == min(r.x, r.y, r.z))
        s = Vector(0.f, -r.z, r.y);
    else if(r.y == min(r.x, r.y, r.z))
        s = Vector(-r.z, 0.f, r.x);
    else if (r.z == min(r.x, r.y, r.z))
        s = Vector(-r.y, r.x, 0.f);
    s = s.normalize();

    Vector t = cross(r, s);

    Matrix M = Matrix::system(r, s, t);

    Matrix Rx = Matrix(
        Float4(1.f, 0.f, 0.f, 0.f), 
        Float4(0.f, cos(angle), -sin(angle), 0.f), 
        Float4(0.f, sin(angle), cos(angle), 0.f), 
        Float4(0.f, 0.f, 0.f, 1.f));

    T = product(product(M, Rx), M.transpose());
    Tinv = T.invert();

}

void Instance::scale(float f) {
    Matrix scale = Matrix(Float4(f, 0.f, 0.f, 0.f), Float4(0.f, f, 0.f, 0.f), Float4(0.f, 0.f, f, 0.f), Float4(0.f, 0.f, 0.f, 1.f));
    T = product(scale, T);
    Tinv = T.invert();
}

void Instance::scale(const Vector& s) {
    Matrix scale = Matrix(Float4(s.x, 0.f, 0.f, 0.f), Float4(0.f, s.y, 0.f, 0.f), Float4(0.f, 0.f, s.z, 0.f), Float4(0.f, 0.f, 0.f, 1.f));
    T = product(scale, T);
    Tinv = T.invert();
}

void Instance::setMaterial(Material* m) {
    archetype->setMaterial(m);
}

void Instance::setCoordMapper(CoordMapper* cm) {
    archetype->setCoordMapper(cm);
}

Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const {
    assert(Tinv != Matrix::zero());
    Ray rayInv = Ray(Tinv * ray.o, Tinv * ray.d);
    Intersection intersectArchetype = archetype->intersect(rayInv, previousBestDistance);
    //since we are not normalizing ray.d, we dont need to change previous best distance
    //ref: Fundamentals of CG 4th edition, Section 13.2 Instancing 
    if (intersectArchetype) {
        Vector normal = Tinv.transpose() * intersectArchetype.normal();
        Intersection intersection(intersectArchetype.distance , ray, intersectArchetype.solid, normal.normalize(), intersectArchetype.local());
        return intersection;
    }
    else
        return Intersection::failure();
}

BBox Instance::getBounds() const {
    BBox archBBox = archetype->getBounds();
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