#ifndef CG1RAYTRACER_MATERIALS_COOKTORRANCE_HEADER
#define CG1RAYTRACER_MATERIALS_COOKTORRANCE_HEADER

#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <core/scalar.h>

namespace rt {

class Texture;

class CookTorranceMaterial : public Material {
public:
    CookTorranceMaterial(Texture* diffuse, Texture* specular, float diffCoeficient, float specCoeficient, float m);
    virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
    virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual Sampling useSampling() const;
private:
    Texture* specular, * diffuse;
    float diffCoeficient, specCoeficient, m;
};

}

#endif