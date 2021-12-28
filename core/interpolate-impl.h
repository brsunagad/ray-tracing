#include "interpolate.h"

namespace rt {

template <typename T>
T lerp(const T& px0, const T& px1, float xPoint) {
    return px0*(1-xPoint)+ px1*xPoint;
}

template <typename T>
T lerpbar(const T& a, const T& b, const T& c, float aWeight, float bWeight) {
    //float cWeight = 1-aWeight-bWeight;
    return a*aWeight + b*bWeight + c*(1-aWeight-bWeight);
}

template <typename T>
T lerp2d(const T& px0y0, const T& px1y0, const T& px0y1, const T& px1y1, float xWeight, float yWeight) {
    return (1-xWeight-yWeight+yWeight*xWeight)*px0y0
    		+ xWeight*(1-yWeight)*px1y0
    		+ yWeight*(1-xWeight)*px0y1
    		+ yWeight*xWeight*px1y1;
}

template <typename T>
T lerp3d(const T& px0y0z0, const T& px1y0z0, const T& px0y1z0, const T& px1y1z0,
    const T& px0y0z1, const T& px1y0z1, const T& px0y1z1, const T& px1y1z1,
    float xPoint, float yPoint, float zPoint)
{
    //we perform 4 interp on x, 2 on y and 1 on z == 2 bilinear interp on xy and linear on z:
	return ((1-xPoint-yPoint+yPoint*xPoint)*px0y0z0 + xPoint*(1-yPoint)*px1y0z0
			+ yPoint*(1-xPoint)*px0y1z0 + yPoint*xPoint*px1y1z0)*(1-zPoint) //first bilinear
			+ ((1-xPoint-yPoint+yPoint*xPoint)*px0y0z1 + xPoint*(1-yPoint)*px1y0z1
			+ yPoint*(1-xPoint)*px0y1z1 + yPoint*xPoint*px1y1z1)*zPoint; //second bilinear
}

}