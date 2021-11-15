#ifndef CG1RAYTRACER_INTEGRATORS_INTEGRATOR_HEADER
#define CG1RAYTRACER_INTEGRATORS_INTEGRATOR_HEADER

#include <core/assert.h>
#include <core/color.h>
#include <rt/world.h>

namespace rt {

class World;
class Ray;

class Integrator {
public:
    Integrator(World* world) : world(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const = 0;
protected:
    World* world;
};

}

#endif