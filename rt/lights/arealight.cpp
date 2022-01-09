#include <rt/lights/arealight.h>
#include <core/color.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>

namespace rt {

LightHit AreaLight::getLightHit(const Point& p) const {
    LightHit lightHit;
    Solid::Sample s = source->sample();

    lightHit.direction = (s.point - p).normalize();
    lightHit.normal = s.normal;
    lightHit.distance = (s.point - p).length() - 0.00015f;

    return lightHit;
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
    RGBColor emission = source->material->getEmission(Point(), Vector(), Vector());
    float cosTheta = abs(dot(irr.normal, irr.direction));

    RGBColor temp = emission * source->getArea() * cosTheta / (irr.distance * irr.distance);

    return temp;
}

AreaLight::AreaLight(Solid* source): source(source) {}

}