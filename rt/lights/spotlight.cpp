#include <rt/lights/spotlight.h>

namespace rt {

SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float power, const RGBColor& intensity):
    position(position),
    direction(direction.normalize()),
    angle(angle),
    power(power),
    intensity(intensity){}

RGBColor SpotLight::getIntensity(const LightHit& irr) const {
    float lobe = dot(-irr.direction, this->direction);
    if (angle > acos(lobe))
        return intensity * (pow(lobe, power) / (irr.distance * irr.distance));
    else
        return RGBColor::rep(0.0f);
}

}
