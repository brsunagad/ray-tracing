#include <rt/integrators/casting.h>

namespace rt {

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {
    Intersection i = world->scene->intersect(ray);
    if(i)
    	return RGBColor::rep(dot(-ray.d.normalize(), i.normal().normalize())); 
    else 
        return RGBColor::rep(0.0f);
}

}
