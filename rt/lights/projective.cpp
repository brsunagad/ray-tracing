#include <rt/lights/projective.h>

namespace rt {

ProjectiveLight::ProjectiveLight(const Point& position, const RGBColor& intensity):
	position(position), intensity(intensity){}

LightHit ProjectiveLight::getLightHit(const Point& p) const {
    Vector dir = position - p;
    LightHit lightHit = { dir.normalize(), dir.length(), -dir.normalize() };
    return lightHit;
}

RGBColor ProjectiveLight::getIntensity(const LightHit& irr) const {
	//mimic a1computeColor from assignment 1
    RGBColor color = RGBColor::rep(0.0f);
    color = color + computeWeight(irr.direction, Point(-0.8f, 0.156f, 0.0f), 64.0f) * RGBColor(0.8f, 0.8f, 1.0f);
    color = color + computeWeight(irr.direction, Point(-0.6f, 0.2f, 0.0f), 64.0f)*0.2f * RGBColor(0.5f, 0.5f, -0.2f);
    color = color + computeWeight(irr.direction, Point(0.285f, 0.0f, 0.0f), 64.0f) * RGBColor(0.2f, 0.3f, 0.4f);
    
    //not dividing by the distance makes it look more "projected" as it does not get darker
    return (intensity - color);//* (1.f / (irr.distance*irr.distance)); 
}

float ProjectiveLight::computeWeight(const Vector& vec, const Point& c, float div) const{
	Point v(vec.x, vec.y, vec.z);
    int numIter = julia(v, c);
    return numIter/(numIter+div);
}

}