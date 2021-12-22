#include <rt/materials/mirror.h>
#include <core/scalar.h>

namespace rt {

MirrorMaterial::MirrorMaterial(float eta, float kappa):eta(eta), kappa(kappa){}

RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    return RGBColor::rep(0.f);
}

RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0.f);
}

Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    float ek_sqr = (eta * eta) + (kappa * kappa);
    Vector ref_dir = -outDir + (2 * dot(outDir, normal) * normal);
    ref_dir = ref_dir.normalize();

    float cos_i = dot(ref_dir, normal);
    float cos_i_sq = cos_i * cos_i;
    float two_eta_cos_i = 2 * eta * cos_i;

    float r_perp = (ek_sqr - two_eta_cos_i + cos_i_sq) / (ek_sqr + two_eta_cos_i + cos_i_sq);
   
    float r_para = ((ek_sqr * cos_i_sq) - two_eta_cos_i + 1) / ((ek_sqr * cos_i_sq) + two_eta_cos_i + 1);

    return SampleReflectance(ref_dir, RGBColor::rep(0.5f * (r_para + r_perp)));
}

Material::Sampling MirrorMaterial::useSampling() const {
    return SAMPLING_ALL;
}

}