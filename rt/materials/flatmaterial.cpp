#include <rt/materials/flatmaterial.h>

namespace rt {

FlatMaterial::FlatMaterial (Texture* texture): texture(texture)
{}

RGBColor FlatMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    return RGBColor::rep(0.0f);
}

RGBColor FlatMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return texture->getColor(texPoint);
}

Material::SampleReflectance FlatMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
//    UNREACHABLE;
    return Material::SampleReflectance();
}

Material::Sampling FlatMaterial::useSampling() const {
    return SAMPLING_NOT_NEEDED;
}

}