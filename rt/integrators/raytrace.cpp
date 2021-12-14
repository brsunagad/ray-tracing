#include <rt/integrators/raytrace.h>

namespace rt {

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {

	RGBColor radiance = RGBColor::rep(0.0f);

    Intersection i = world->scene->intersect(ray);

    if(i){
    	// Hit was successfull, now we calculate radiance

    	//emission
		Point texPoint = i.local(); //This will change when implementing textures
    	radiance = radiance + i.solid->material->getEmission(texPoint, i.normal().normalize(), -ray.d); //Dummy returns 0, but future materials wont

 		//iterate over every lightsource
        for( auto light : world->light){
        	//get the light hit from the lightsource
            LightHit lh = light->getLightHit(i.hitPoint());

            //Compute shadow ray
            //we add an offset to the origin not to get self intersections
            Ray shadowray(i.hitPoint() + i.normal()*FLT_MIN, lh.direction);

            // If shadow ray and primary ray are on the same side
            if(dot(i.normal(), shadowray.d) > 0.0f){
            	// ray into the
                Intersection shadowI = world->scene->intersect(shadowray, lh.distance);
                
                // If there was no intersection, we compute the intensity and reflectance of the material
                if(!shadowI){
                    RGBColor intensity = world->light[i]->getIntensity(lh);
                    RGBColor reflectance = i.solid->material->getReflectance(texPoint, i.normal(), -ray.d, -shadowray.d);
                    radiance = radiance + intensity * reflectance;
                }
            } //else: theres shadow, we dont compute light
        } 
    } // else: No hit, we return black
    return radiance;
}

}