#include <rt/lights/arealight.h>
#include <core/color.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>

namespace rt {

LightHit AreaLight::getLightHit(const Point& p) const {
    LightHit lightHit;
    Solid::Sample s = source->sample();
    samplePoint = (s.point);
    lightHit.direction = (s.point - p).normalize();
    lightHit.normal = s.normal;
    lightHit.distance = (s.point - p).length() - 0.00015f;
    lightHit.hitPoint = s.point;
    return lightHit;
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
    RGBColor emission = source->material->getEmission(irr.hitPoint, Vector(), Vector());
    float cosTheta = abs(dot(irr.normal, irr.direction));

    RGBColor temp = emission * source->getArea() * cosTheta / (irr.distance * irr.distance);

    return temp * scale;
}

AreaLight::AreaLight(Solid* source, int scale ): source(source), scale(scale) {}

}