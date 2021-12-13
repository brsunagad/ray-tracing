#include <rt/lights/pointlight.h>

#include <core/vector.h>

namespace rt {

PointLight::PointLight(const Point& position, const RGBColor& intensity): potition(position), intensity(intensity){}

LightHit PointLight::getLightHit(const Point& p) const {
    Vector dir = position - p;
    LightHit lighthit = { dir.normalize(), dir.length(), -dir.normalize() };
    return LightHit
}

RGBColor PointLight::getIntensity(const LightHit& irr) const {
    return intensity * (1.f / (irr.distance * irr.distance));
}

}
