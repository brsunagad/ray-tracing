#include <rt/primmod/bmap.h>
#include <core/assert.h>

namespace rt {

BumpMapper::BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale):
	base(base), bumpmap(bumpmap), bv1(bv1), bv2(bv2), bv3(bv3), vscale(vscale)
{
	Ou = base->getVectoru();
	Ov = base->getVectorv();

	// Ou = bv1-bv2;
	// Ov = bv1-bv3;
}

BBox BumpMapper::getBounds() const {
    return base->getBounds();
}

// TODO: A full implementation has to make use of the coord mappers as well!
Intersection BumpMapper::intersect(const Ray& ray, float previousBestDistance) const {
    Intersection intersectBase = base->intersect(ray, previousBestDistance);

    if (intersectBase) {
    	Vector N = intersectBase.normal();
        Point local = intersectBase.local();

        // Apply triangular coordmap for the bumtex
        Point texPoint = local.x * bv1 + local.y * bv2 + local.z * bv3;

        //Color is given in RGB but we will use its lumiance:
        float Y_Bx = bumpmap->getColorDX(texPoint).luminance();
        float Y_By = bumpmap->getColorDY(texPoint).luminance();

        Vector D = vscale*(Y_Bx*cross(N,Ou) - Y_By*cross(N,Ov));
        N = N + D;


		// std::cout << "Y_Bx: " << Y_Bx << ", Y_By: " << Y_By << std::endl;
  //       std::cout << "D = (" << D.x << ", " << D.y << ", " << D.z << ")" << std::endl << std::endl;

        return Intersection(intersectBase.distance, ray, intersectBase.solid, N.normalize(), local);
    }
    else
        return Intersection::failure();
}

void BumpMapper::setMaterial(Material* m) {
    base->setMaterial(m);
}

void BumpMapper::setCoordMapper(CoordMapper* cm) {
    base->setCoordMapper(cm);
}

}