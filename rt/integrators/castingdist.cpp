#include <rt/integrators/castingdist.h>

namespace rt {

RayCastingDistIntegrator::RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist)
    : Integrator(world)
{
	this->nearColor = nearColor;
	this->farColor = farColor;
	this->nearDist = nearDist;
	this->farDist = farDist;
}

RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const {

    Intersection i = world->scene->intersect(ray);

    if(i){
        RGBColor result;
        if (i.distance > farDist) 
            result = farColor;
        else if(i.distance < nearDist)
            result = nearColor;
        else 
        	//interpolation
            result = (i.distance - nearDist)/(farDist-nearDist)*farColor+(farDist-i.distance)/(farDist-nearDist)*nearColor;
        
        return result * RGBColor::rep(dot(-ray.d.normalize(), i.normal().normalize())); 

    }
    else 
        return RGBColor::rep(0.0f);
}

}
