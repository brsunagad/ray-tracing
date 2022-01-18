#ifndef CG1RAYTRACER_PRIMMOD_BMAP_HEADER
#define CG1RAYTRACER_PRIMMOD_BMAP_HEADER

#include <rt/primitive.h>
#include <rt/solids/triangle.h>
#include <rt/textures/texture.h>
#include <rt/intersection.h>

namespace rt {

class Triangle;
class Texture;

class BumpMapper : public Primitive {
public:
    BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale);
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
private:
	Triangle* base;
	Texture* bumpmap;
	Point bv1, bv2, bv3;
	float vscale;
	Vector Ou, Ov; //vectors living in triangle plane
};

}

#endif