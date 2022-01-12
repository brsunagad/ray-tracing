#include <rt/solids/enviromentMap.h>

namespace rt {

EnviromentMap::EnviromentMap(CoordMapper* texMapper, Material* material): 
    Solid(texMapper, material) {}

BBox EnviromentMap::getBounds() const {
    return BBox::full();
}

Intersection EnviromentMap::intersect(const Ray& ray, float previousBestDistance) const {
    //always return infinity
    if (previousBestDistance == FLT_MAX){
        Ray newr(Point(FLT_MAX,FLT_MAX,FLT_MAX), Vector(-1,-1,-1));
        return Intersection(FLT_MAX, newr, this, -ray.d, Point(FLT_MAX,FLT_MAX,FLT_MAX));
    }
    else 
        return Intersection::failure();

}

Solid::Sample EnviromentMap::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float EnviromentMap::getArea() const {
	// Infinite area
    return FLT_MAX;
}

}