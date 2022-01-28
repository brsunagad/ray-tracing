#include <rt/integrators/recraytrace.h>
#include <rt/intersection.h>
#include <rt/lights/light.h>
#include <rt/world.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>
#include <rt/coordmappers/coordmapper.h>
namespace rt {

RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
    int max_rec_depth = depth;
    return recurse(ray, max_rec_depth);
}
RGBColor RecursiveRayTracingIntegrator::recurse(const Ray& ray, int& depth) const {
    RGBColor radiance = RGBColor::rep(0.0f);

    depth--;
    if (depth == 0)
        return radiance;

    RGBColor emission, reflectance, intensity;
    Point texPoint;
    Intersection intersection = world->scene->intersect(ray);
    if (intersection) {
        texPoint = intersection.solid->texMapper->getCoords(intersection);
        Material::Sampling sampling = intersection.solid->material->useSampling();
        if (sampling == Material::SAMPLING_NOT_NEEDED || sampling == Material::SAMPLING_SECONDARY) {
            emission = intersection.solid->material->getEmission(texPoint, intersection.normal(), -ray.d);
            radiance = radiance + emission;
            for (auto light : world->light) {
                LightHit lightHit = light->getLightHit(intersection.hitPoint());
                Ray shadowRay(intersection.hitPoint() + intersection.normal() * 0.0001, lightHit.direction);
                if (dot(intersection.normal(), shadowRay.d) > 0.0f) {
                    Intersection shadowI = world->scene->intersect(shadowRay, lightHit.distance);
                    if (!shadowI) {
                        intensity = light->getIntensity(lightHit);
                        reflectance = intersection.solid->material->getReflectance(texPoint, intersection.normal(), -ray.d, -shadowRay.d);
                        radiance = radiance + intensity * reflectance;
                    }
                }
            }
        }
        if (sampling == Material::SAMPLING_ALL || sampling == Material::SAMPLING_SECONDARY) {
            Material::SampleReflectance sampleReflectance = intersection.solid->material->getSampleReflectance(texPoint, intersection.normal(), -ray.d);
            Ray secondaryRay(intersection.hitPoint() + sampleReflectance.direction * 0.0001, sampleReflectance.direction);
            radiance = radiance + sampleReflectance.reflectance * recurse(secondaryRay, depth);
        }
    }
    return radiance.clamp();
}
}