#include <rt/lights/directional.h>
#include <core/scalar.h>
#include <core/vector.h>

namespace rt {

DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color): direction(direction.normalize()), color(color){}

LightHit DirectionalLight::getLightHit(const Point& p) const {
    LightHit lightHit = { -direction, FLT_MAX, direction };
    return lightHit;
}

RGBColor DirectionalLight::getIntensity(const LightHit& irr) const {
    return color;
}

}
