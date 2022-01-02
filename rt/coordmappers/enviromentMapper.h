#ifndef CG1RAYTRACER_COORDMAPPERS_ENVIROMENT_HEADER
#define CG1RAYTRACER_COORDMAPPERS_ENVIROMENT_HEADER

#include <rt/coordmappers/coordmapper.h>
#include <core/vector.h>
#include <rt/intersection.h>

namespace rt {

class Vector;

class EnviromentMapper : public CoordMapper {
public:
    EnviromentMapper();
    virtual Point getCoords(const Intersection& hit) const;
};

}

#endif