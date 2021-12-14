#ifndef CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER

#include <core/scalar.h>
#include <core/vector.h>
#include <rt/lights/pointlight.h>
#include <core/julia.h>

namespace rt {

class ProjectiveLight : public Light {
private: 
	Point position;
	RGBColor intensity;

	float computeWeight(const Vector& v, const Point& c, float div) const;
public:
	ProjectiveLight() {}
	ProjectiveLight(const Point& position, const RGBColor& intensity);
	virtual LightHit getLightHit(const Point& p) const;
    virtual RGBColor getIntensity(const LightHit& irr) const;
};

}

#endif