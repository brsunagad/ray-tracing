#include <rt/solids/aabox.h>

namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material)
{
    this->maxCorner = max(corner1,corner2);
    this->minCorner = min(corner1,corner2);
    this->material = material;
    this->texMapper = texMapper;
}

BBox AABox::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
    return 2*(maxCorner.x-minCorner.x + maxCorner.y-minCorner.y + maxCorner.z-minCorner.z);
}

Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const {

	// std::cout << "AABOX" << std::endl;
	// std::cout << "--> Ray vector = (" << ray.d.x << ", " << ray.d.y << ", " << ray.d.z << ")" << std::endl;
	// std::cout << "--> Ray Origin = (" << ray.o.x << ", " << ray.o.y << ", " << ray.o.z << ")" << std::endl;
	// std::cout << "--> Prev distance = " << previousBestDistance << std::endl;

	float xnear, xfar, ynear, yfar, znear, zfar;
	float invdx = 1.0f/ray.d.x;
	float invdy = 1.0f/ray.d.y;
	float invdz = 1.0f/ray.d.z;

	// if the ray goes in negative direction, far and near are changed
    if (invdx > 0){
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

    float maxNear = max(xnear,ynear,znear);
    float minfar = min(xfar,yfar,zfar);

 //    std::cout << "Nears: (" << xnear << ", " << ynear << ", " << znear << ")" << std::endl;
	// std::cout << "Fars: (" << xfar << ", " << yfar << ", " << zfar << ")" << std::endl;
	// std::cout << "Maxmins: (" << maxNear << ", " << minfar << std::endl;


    if (maxNear <= minfar && maxNear >= 0 && maxNear<previousBestDistance)
    {
    	// Decide which face of the BBox is intersecting
    	Vector normal;
	    if(maxNear == xnear){
	        if (xnear < xfar)
	           normal = Vector(-1.0f, 0.f, 0.f);
	        else 
	           normal = Vector(1.0f, 0.f, 0.f);
	    }
	    else if(maxNear == ynear){
	        if (ynear < yfar)
	            normal = Vector(0.f, -1.0f, 0.f);
	        else 
	            normal = Vector(0.f, 1.0f, 0.f);
	    }      
	    else{
	        if (znear < zfar)
	            normal = Vector(0.f, 0.f, 1.0f);
	        else 
	            normal = Vector(0.f, 0.f, -1.0f);
	    } 

    	return Intersection(maxNear,ray, this, normal, ray.getPoint(maxNear));
    } else
    	return Intersection::failure();
}

}
