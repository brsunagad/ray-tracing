#include <rt/materials/fuzzymirror.h>
#include <core/scalar.h>
#include <rt/solids/disc.h>

namespace rt {

FuzzyMirrorMaterial::FuzzyMirrorMaterial(float eta, float kappa, float fuzzyangle): eta(eta), kappa(kappa), fuzzyangle(fuzzyangle)
{}

RGBColor FuzzyMirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    return RGBColor::rep(0.f);

}

RGBColor FuzzyMirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0.f);

}

Material::SampleReflectance FuzzyMirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	Vector reflectedDirection = -outDir + 2 * dot(outDir, normal) * normal;

	Disc disc(texPoint + reflectedDirection.normalize(), reflectedDirection.normalize(), tan(fuzzyangle), nullptr, nullptr);

	Vector dir = disc.sample().point - texPoint;

	float esks = sqr(eta) + sqr(kappa);
	float cosTheta = dot(dir, normal);// (dir.length() * normal.length());

	float r_parallel = (esks * sqr(cosTheta) - 2 * eta * cosTheta + 1) / (esks * sqr(cosTheta) + 2 * eta * cosTheta + 1);
	float r_perpendicular = (esks - 2 * eta * cosTheta + sqr(cosTheta)) / (esks + 2 * eta * cosTheta + sqr(cosTheta));

	float reflectance = 0.5f * (r_parallel + r_perpendicular);

	return SampleReflectance(dir.normalize(), RGBColor::rep(reflectance));
}

Material::Sampling FuzzyMirrorMaterial::useSampling() const {
    return SAMPLING_ALL;
}

}
