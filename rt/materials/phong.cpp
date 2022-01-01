#define _USE_MATH_DEFINES
#include <core/scalar.h>
#include <rt/materials/phong.h>
#include <rt/textures/texture.h>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent): specular(specular), exponent(exponent){}

RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    Vector reflection = (inDir - 2 * dot(inDir, normal) * normal).normalize();
    float cosTheta = dot(reflection, outDir);
    if (cosTheta < 0 || dot(-inDir, normal) < 0)
        return RGBColor(0, 0, 0);
    return specular->getColor(texPoint) * (powf(cosTheta, exponent) * (exponent + 2) * dot(normal, -inDir)) / (2 * pi);
}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0.0f);
}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return Material::SampleReflectance();
}

Material::Sampling PhongMaterial::useSampling() const {
    return SAMPLING_NOT_NEEDED;
}

}