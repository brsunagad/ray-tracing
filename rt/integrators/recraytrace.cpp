#include <rt/integrators/recraytrace.h>
#include <rt/intersection.h>
#include <rt/lights/light.h>
#include <rt/world.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>
#include <rt/coordmappers/coordmapper.h>
namespace rt {

RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
    int max_rec_depth = 6;
    return recurse(ray, max_rec_depth);
}
RGBColor RecursiveRayTracingIntegrator::recurse(const Ray& ray, int& depth) const {
    RGBColor totalRadiance = RGBColor::rep(0.0f);

    depth--;
    if (depth == 0)
        return totalRadiance;

    RGBColor emission, reflectance, intensity;
    Point texPoint;
    Intersection intersection = world->scene->intersect(ray);
    if (intersection) {
        texPoint = intersection.solid->texMapper->getCoords(intersection);
        Material::Sampling sampling = intersection.solid->material->useSampling();
        if (sampling == Material::SAMPLING_NOT_NEEDED || sampling == Material::SAMPLING_SECONDARY) {
            emission = intersection.solid->material->getEmission(texPoint, intersection.normal(), -ray.d);
            totalRadiance = totalRadiance + emission;
            for (int i = 0; i < world->light.size(); i++) {
                LightHit lightHit = world->light[i]->getLightHit(intersection.hitPoint());
                //Shift the ray origin towards it's direction by an offset, to avoid self intersection
                Ray shadowRay(intersection.hitPoint() + intersection.normal() * 0.0001, lightHit.direction);
                if (dot(intersection.normal(), shadowRay.d) > 0.0f) {
                    Intersection shaIntersec = world->scene->intersect(shadowRay, lightHit.distance);
                    //If no intersection of shadow ray, or the intersection distance greater than distance to light source, update radiance
                    if (!shaIntersec) {
                        intensity = world->light[i]->getIntensity(lightHit);
                        reflectance = intersection.solid->material->getReflectance(texPoint, intersection.normal(), -ray.d, -shadowRay.d);
                        totalRadiance = totalRadiance + intensity * reflectance;
                    }
                }
            }
        }
        if (sampling == Material::SAMPLING_ALL || sampling == Material::SAMPLING_SECONDARY) {
            Material::SampleReflectance sampleReflectance = intersection.solid->material->getSampleReflectance(texPoint, intersection.normal(), -ray.d);
            Ray secondaryRay(intersection.hitPoint() + intersection.normal() * 0.0001, sampleReflectance.direction);
            totalRadiance = totalRadiance + sampleReflectance.reflectance * getRadiance(secondaryRay);
        }
    }
    return totalRadiance;
}
}