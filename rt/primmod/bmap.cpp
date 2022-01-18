#include <rt/primmod/bmap.h>
#include <core/assert.h>

namespace rt {

BumpMapper::BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale)
{
    /* TODO */
}

BBox BumpMapper::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

// TODO: A full implementation has to make use of the coord mappers as well!
Intersection BumpMapper::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ NOT_IMPLEMENTED;
}

void BumpMapper::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void BumpMapper::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

}