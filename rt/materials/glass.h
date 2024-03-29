#ifndef CG1RAYTRACER_MATERIALS_GLASS_HEADER
#define CG1RAYTRACER_MATERIALS_GLASS_HEADER

#include <rt/materials/material.h>

namespace rt {

class GlassMaterial : public Material {
private: float eta;
       Texture* texture = nullptr;
public:
    GlassMaterial(float eta, Texture* texture);
    virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
    virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual Sampling useSampling() const;
    float fresnel(const Vector I, const Vector& N, const float& ior) const;
    Vector refract(const Vector I, const Vector& N, const float& ior) const;
};

}

#endif