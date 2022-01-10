
#include <rt/materials/cooktorrance.h>

namespace rt {

CookTorranceMaterial::CookTorranceMaterial(Texture* diffuse, Texture* specular, float diffCoeficient, float specCoeficient, float m):
	specular(specular), diffuse(diffuse), diffCoeficient(diffCoeficient), specCoeficient(specCoeficient), m(m){
		float sum = diffCoeficient+specCoeficient;
		if (sum > 1){ //normalize if the sum is above 1
			this->diffCoeficient = (diffCoeficient/sum);
			this->specCoeficient = (specCoeficient/sum);
		}
	}

RGBColor CookTorranceMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    float NdotV = dot(normal, -inDir);
    if (NdotV < 0) return RGBColor(0, 0, 0);

    //difussion
    RGBColor kd = (1.f / pi) * NdotV * diffuse->getColor(texPoint);

    //Specular
    Vector H = (outDir-inDir).normalize();

    float NdotI = dot(normal, outDir);
    float NdotH = dot(normal, H);
    float VdotH = dot(-inDir, H);

    float F = pow(1+NdotV,0.2);
    float D = pow(NdotH,log(2)/log(cos(m)));
    float G = std::min(1.0f,std::min(NdotH*NdotV/VdotH,NdotH*NdotI/VdotH)); 

    RGBColor ks = F*D*G/(pi*NdotV*NdotI)*specular->getColor(texPoint);


    return kd*diffCoeficient + ks*specCoeficient;
}

RGBColor CookTorranceMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return RGBColor::rep(0.0f);
}

Material::SampleReflectance CookTorranceMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return Material::SampleReflectance();
}

Material::Sampling CookTorranceMaterial::useSampling() const {
	return SAMPLING_NOT_NEEDED;
}

}