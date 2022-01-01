#define _USE_MATH_DEFINES
#include <rt/materials/lambertian.h>
#include <rt/textures/texture.h>
#include <core/scalar.h>
namespace rt {

LambertianMaterial::LambertianMaterial(Texture* emission, Texture* diffuse):emission(emission), diffuse(diffuse){}

RGBColor LambertianMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
	return (1.f / pi) * dot(normal, -inDir) * diffuse->getColor(texPoint);
}

RGBColor LambertianMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return emission->getColor(texPoint);
}

Material::SampleReflectance LambertianMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return Material::SampleReflectance();
}

Material::Sampling LambertianMaterial::useSampling() const {
	return SAMPLING_NOT_NEEDED;
}

}