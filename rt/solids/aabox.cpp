#include <rt/solids/aabox.h>
#include <tuple>

namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material): 
	maxCorner(max(corner1, corner2)),
	minCorner(min(corner1, corner2)),
	Solid(texMapper, material){}


BBox AABox::getBounds() const {
	return BBox(minCorner, maxCorner);
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
    return 2*(maxCorner.x-minCorner.x + maxCorner.y-minCorner.y + maxCorner.z-minCorner.z);
}

Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const {

	std::cout << "AABOX" << std::endl;
	std::cout << "--> Ray vector = (" << ray.d.x << ", " << ray.d.y << ", " << ray.d.z << ")" << std::endl;
	std::cout << "--> Ray Origin = (" << ray.o.x << ", " << ray.o.y << ", " << ray.o.z << ")" << std::endl;
	std::cout << "--> Prev distance = " << previousBestDistance << std::endl << std::endl;

	std::cout << "--> minCorner = (" << minCorner.x << ", " << minCorner.y << ", " << minCorner.z << ")" << std::endl;
	std::cout << "--> maxCorner = (" << maxCorner.x << ", " << maxCorner.y << ", " << maxCorner.z << ")" << std::endl << std::endl;

	float xnear, xfar, ynear, yfar, znear, zfar;
	float invdx = 1.0f/ray.d.x;
	float invdy = 1.0f/ray.d.y;
	float invdz = 1.0f/ray.d.z;

	// if the ray goes in negative direction, far and near are changed
    if (invdx >= 0){
    	xnear = (minCorner.x - ray.o.x)*invdx;
	    xfar = (maxCorner.x - ray.o.x)*invdx;
    } else {
    	xfar = (minCorner.x - ray.o.x)*invdx;
	    xnear = (maxCorner.x - ray.o.x)*invdx;
    }
    if (invdy >= 0){
	    ynear = (minCorner.y - ray.o.y)*invdy;
	    yfar = (maxCorner.y - ray.o.y)*invdy;
    } else {
	    yfar = (minCorner.y - ray.o.y)*invdy;
	    ynear = (maxCorner.y - ray.o.y)*invdy;
    }
    if (invdz >= 0){
 	    znear = (minCorner.z - ray.o.z)*invdz;
	    zfar = (maxCorner.z - ray.o.z)*invdz;
    } else {
    	zfar = (minCorner.z - ray.o.z)*invdz;
	    znear = (maxCorner.z - ray.o.z)*invdz;
    }

    float maxNear;
    float minfar;

    std::cout << "Nears: (" << xnear << ", " << ynear << ", " << znear << ")" << std::endl;
	std::cout << "Fars: (" << xfar << ", " << yfar << ", " << zfar << ")" << std::endl;

    // Try intersection on xy plane
    if ((xnear > yfar) || (ynear > xfar)) 
        return Intersection::failure(); //miss
    maxNear = std::max(xnear, ynear);
    minfar = std::min(xfar, yfar);

    // Try intersection on prev and z plane
    if ((maxNear > zfar) || (znear > minfar)) 
        return Intersection::failure(); //miss
    maxNear = std::max(maxNear, znear);
    minfar = std::min(minfar, zfar);

	std::cout << "Maxmins: (" << maxNear << ", " << minfar << ")" << std::endl;

	// Decide which face of the aaBox is intersecting
	Vector normal;
    if(maxNear == xnear){
    	normal = Vector(-1.0f, 0.f, 0.f);
        // if (xnear < xfar)
        //    normal = Vector(-1.0f, 0.f, 0.f);
        // else 
        //    normal = Vector(1.0f, 0.f, 0.f);
    }
    else if(maxNear == ynear){
    	normal = Vector(0.f, -1.0f, 0.f);
        // if (ynear < yfar)
        //     normal = Vector(0.f, -1.0f, 0.f);
        // else 
        //     normal = Vector(0.f, 1.0f, 0.f);
    }      
    else{
    	normal = Vector(0.f, 0.f, -1.0f);
        // if (znear < zfar)
        //     normal = Vector(0.f, 0.f, 1.0f);
        // else 
        //     normal = Vector(0.f, 0.f, -1.0f);
    } 

	std::cout << "-->Normal: (" << normal.x << ", " << normal.y << ", " << normal.z << ")" << std::endl;

	if(maxNear <= minfar && maxNear >= 0 && maxNear < previousBestDistance){
		setIntersectionValues(maxNear, minfar, normal);
		return Intersection(maxNear,ray, this, normal, ray.getPoint(maxNear));
	} else
		return Intersection::failure(); //Not best distance
	
}
void AABox::setIntersectionValues(float t1, float t2, Vector& normal) const{
	this->t1 = t1;
	this->t2 = t2;
	this->_normal = normal;

}

std::tuple<float, float, Vector> AABox::getIntersectionValues() const {
	return std::make_tuple(t1, t2, _normal);
}

}
