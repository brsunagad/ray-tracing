#include <rt/coordmappers/enviromentMapper.h>

namespace rt {

EnviromentMapper::EnviromentMapper(){}

Point EnviromentMapper::getCoords(const Intersection& hit) const {
   return Point(hit.ray.d.x, hit.ray.d.y, hit.ray.d.z);
}

}