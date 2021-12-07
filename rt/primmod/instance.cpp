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

    if (intersectArchetype) {
        Vector normal = Tinv.transpose() * intersectArchetype.normal();
        Intersection intersection(intersectArchetype.distance , ray, intersectArchetype.solid, normal.normalize(), intersectArchetype.local());
        return intersection;
    }
    else
        return Intersection::failure();
}

BBox Instance::getBounds() const {
    return BBox(T * archetype->getBounds().min, T * archetype->getBounds().max);
}

}