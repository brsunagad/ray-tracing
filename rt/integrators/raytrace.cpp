#include <rt/integrators/raytrace.h>

namespace rt {

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {
	// still to do!!!!!

	
    Intersection i = world->scene->intersect(ray);
    if(i)
    	return RGBColor::rep(dot(-ray.d.normalize(), i.normal().normalize())); 
    else 
        return RGBColor::rep(0.0f);
}

}