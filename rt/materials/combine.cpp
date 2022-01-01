#include <rt/materials/combine.h>

namespace rt {

CombineMaterial::CombineMaterial()
{
    /* TODO */
}

void CombineMaterial::add(Material* m, float w) {
    materials.push_back(std::make_pair(m, w));
}

RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    RGBColor reflectance = RGBColor::rep(0.f);
    for (auto m : materials) {
        reflectance = reflectance + m.first->getReflectance(texPoint, normal, outDir, inDir) * m.second;
    }

    return reflectance;
}

RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    RGBColor emissions = RGBColor::rep(0.f);
    for (size_t i = 0; i < materials.size(); i++) {
        emissions = emissions + materials[i].first->getEmission(texPoint, normal, outDir) * materials[i].second;
    }

    return emissions;
}

Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    SampleReflectance sampleRef;
    RGBColor reflectance = RGBColor::rep(0.f);
    for (auto m : materials) {
        sampleRef = m.first->getSampleReflectance(texPoint, normal, outDir);
        reflectance = reflectance + sampleRef.reflectance * m.second; 
    }
    return SampleReflectance(sampleRef.direction, reflectance);
}

Material::Sampling CombineMaterial::useSampling() const {
    return SAMPLING_SECONDARY;
}

}