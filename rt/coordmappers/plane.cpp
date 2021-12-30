#include <rt/coordmappers/plane.h>

namespace rt {

PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2) {
    Vector normal = cross(e1, e2);
    projectionMatrix = Matrix::system(e1, e2, normal).invert();
}

Point PlaneCoordMapper::getCoords(const Intersection& hit) const {
    return projectionMatrix * hit.local();
}

}