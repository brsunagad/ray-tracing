#ifndef CG1RAYTRACER_SOLIDS_ENVIROMENTMAP_HEADER
#define CG1RAYTRACER_SOLIDS_ENVIROMENTMAP_HEADER

#include <rt/solids/solid.h>

namespace rt {

class EnviromentMap : public Solid {
public:
    EnviromentMap() {}
    EnviromentMap(CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual Sample sample() const;
    virtual float getArea() const;
};

}

#endif