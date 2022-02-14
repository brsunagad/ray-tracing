#ifndef CG1RAYTRACER_LIGHTS_AREALIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_AREALIGHT_HEADER

#include <rt/lights/light.h>
#include <rt/solids/solid.h>
namespace rt {

class Solid;

class AreaLight : public Light {
private:
    Solid *source;
    int scale;
    Point& samplePoint = Point();
public:
    AreaLight() {}
    AreaLight(Solid* source, int scale = 1);
    virtual LightHit getLightHit(const Point& p) const;
    virtual RGBColor getIntensity(const LightHit& irr) const;
};

}

#endif
