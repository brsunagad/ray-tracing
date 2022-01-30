#include <rt/materials/glass.h>
#include <core/scalar.h>
#include <core/random.h>
namespace rt {

    GlassMaterial::GlassMaterial(float eta, Texture* texture) : eta(eta), texture(texture) {
        isGlass = true;
    }

RGBColor GlassMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    return RGBColor::rep(0.0f);
}

RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    if(texture != nullptr)
        return texture->getColor(texPoint);
    else
        return RGBColor::rep(0.0f);

}

Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    float fr = fresnel(-outDir, normal, eta);

    if (fr >= 1) {
        Vector reflection = (-outDir + (2 * dot(outDir, normal) * normal)).normalize();
        return SampleReflectance(reflection.normalize(), RGBColor::rep(1.f));
    }
    else if (random() < 0.3f) {
        Vector reflection = (-outDir + (2 * dot(outDir, normal) * normal)).normalize();
        return SampleReflectance(reflection.normalize(), 2 * RGBColor::rep(fr));
    }
    else {      
        Vector refraction = refract(-outDir, normal, eta);
        float costheta = dot(-outDir, normal);
        float ni = 1, nt = eta;
        if (costheta > 0)
            std::swap(ni, nt);
        return SampleReflectance(refraction.normalize(), 2 *sqr(ni / nt)* RGBColor::rep((1.f - fr)));//multiplying 2 gave better result
    }
}

Material::Sampling GlassMaterial::useSampling() const {
    return Material::SAMPLING_ALL;
}

Vector GlassMaterial::refract(const Vector I, const Vector& N, const float& ior) const
{//source: https://www.scratchapixel.com/code.php?id=32&origin=/lessons/3d-basic-rendering/phong-shader-BRDF
    float cosi = dot(I, N);
    float etai = 1, etat = ior;
    Vector n = N;
    if (cosi < 0) { cosi = -cosi; }
    else { std::swap(etai, etat); n = -N; }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    if (k < 0) {
        return Vector::rep(0.f);
    }
    else
        return eta * I + (eta * cosi - sqrtf(k)) * n;
}

float GlassMaterial::fresnel(const Vector I, const Vector& N, const float& ior) const
{//source: https://www.scratchapixel.com/code.php?id=32&origin=/lessons/3d-basic-rendering/phong-shader-BRDF
    float kr;
    float cosi = dot(I, N);
    float etai = 1, etat = ior;
    if (cosi > 0) { std::swap(etai, etat); }
    // Compute sini using Snell's law
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    // Total internal reflection
    if (sint >= 1) {
        kr = 1;
    }
    else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        kr = (Rs * Rs + Rp * Rp) * 0.5;
    }
    // As a consequence of the conservation of energy, transmittance is given by:
    // kt = 1 - kr;
    return kr;
}

}