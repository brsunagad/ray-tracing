#ifndef CG1RAYTRACER_COORDMAPPERS_TMAPPER_HEADER
#define CG1RAYTRACER_COORDMAPPERS_TMAPPER_HEADER

#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>
#include <core/float4.h>
namespace rt {

class TriangleMapper : public CoordMapper {
private:
    Point tv0, tv1, tv2;
public:
    TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2);
    TriangleMapper(Point ntv[3]);
    virtual Point getCoords(const Intersection& hit) const;
};

}



#endif