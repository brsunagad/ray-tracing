void a_julia();
void a_cameras();
void a_solids();
void a_indexing();
void a_instancing();
void a_lighting();
void a_materials();
void a_textures();
void a_local();
void a_mappers();
void a_distributed();
void a_smooth();
void a_bumpmappers();

#include <rt/coordmappers/spherical.h>
#include <rt/intersection.h>
#include <rt/ray.h>


int main(int argc, char* argv[]) {

	rt::CoordMapper* test = new rt::SphericalCoordMapper(rt::Point(.5f,.3f,-.1f),rt::Vector(0.1f,2,5),rt::Vector(0.5f,-0.9f,6));
	rt::Intersection hit = rt::Intersection(0,nullptr,nullptr,rt::Vector(0,1,0),rt::Point(0.8f, 0.2f, 0.0f));

	test->getCoords(hit);

    // a_materials();
    // a_textures();
    // a_local();
    // a_mappers();
    // a_distributed();
    // a_smooth();
    return 0;
}