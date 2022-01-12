#include <rt/coordmappers/enviromentMapper.h>

namespace rt {

EnviromentMapper::EnviromentMapper(){}

Point EnviromentMapper::getCoords(const Intersection& hit) const {
   return Point(hit.normal().x, hit.normal().y, hit.normal().z);
}

}