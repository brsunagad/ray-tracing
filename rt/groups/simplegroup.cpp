#include <rt/groups/simplegroup.h>

namespace rt {

BBox SimpleGroup::getBounds() const {
    BBox bbox = BBox::empty() ;
    for (auto p : primitives) {
        bbox.extend(p->getBounds());
    }
    return bbox;
}

Intersection SimpleGroup::intersect( const Ray& ray, float previousBestDistance) const {
    Intersection result = Intersection::failure();
    Intersection temp;
    for(auto p : primitives) {
    	temp = p->intersect(ray, previousBestDistance);
    	if (temp){
            previousBestDistance = temp.distance;
    		result = temp;
        }
	}
	return result;
}

void SimpleGroup::rebuildIndex() {
    //do nothing
}

void SimpleGroup::add(Primitive* p) {
    primitives.push_back(p);
}

void SimpleGroup::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void SimpleGroup::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

}
