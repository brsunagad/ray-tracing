#ifndef CG1RAYTRACER_PRIMMOD_ANIMATED_HEADER
#define CG1RAYTRACER_PRIMMOD_ANIMATED_HEADER

#include <core/vector.h>
#include <rt/primitive.h>
#include <core/matrix.h>
#include <core/random.h>

namespace rt {

class AnimatedPrimitive : public Primitive {
public:
    AnimatedPrimitive(Primitive* aniPrimitive, Vector transV);
    Primitive* content();

    void changeMovement(const Vector& t);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
private:
    Vector transV;
    Matrix T;
    Primitive* aniPrimitive;
};

}

#endif