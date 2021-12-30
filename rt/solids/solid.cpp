#include <rt/solids/solid.h>
#include <rt/coordmappers/world.h>

namespace rt {

Solid::Solid(CoordMapper* texMapper, Material* material):  material(material){
    if (texMapper)
        this->texMapper = texMapper;
    else {
        CoordMapper* worldMapper = new WorldMapper();
        this->texMapper = worldMapper;
    }
}

}
