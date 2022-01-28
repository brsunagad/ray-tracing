#ifndef CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER
#define CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER

#include <rt/integrators/integrator.h>

namespace rt {

class RecursiveRayTracingIntegrator : public Integrator {
public:
    int depth;
    RecursiveRayTracingIntegrator(World* world, int depth) : Integrator(world), depth(depth) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
    RGBColor recurse(const Ray& ray, int& depth) const;
};

}

#endif