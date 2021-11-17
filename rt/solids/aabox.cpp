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

	std::cout << "AABOX" << std::endl;
	std::cout << "--> Ray vector = (" << ray.d.x << ", " << ray.d.y << ", " << ray.d.z << ")" << std::endl;
	std::cout << "--> Ray vector = (" << ray.o.x << ", " << ray.o.y << ", " << ray.o.z << ")" << std::endl;
	std::cout << "--> Prev distance = " << previousBestDistance << std::endl;

	float xnear, xfar, ynear, yfar, znear, zfar;
	// if the ray goes in negative direction, far and near are changed
    if (ray.d.x >= 0){
    	xnear = (minCorner.x - ray.o.x)/ray.d.x;
	    xfar = (maxCorner.x - ray.o.x)/ray.d.x;
    } else {
    	xfar = (minCorner.x - ray.o.x)/ray.d.x;
	    xnear = (maxCorner.x - ray.o.x)/ray.d.x;
    }
    if (ray.d.y >= 0){
	    ynear = (minCorner.y - ray.o.y)/ray.d.y;
	    yfar = (maxCorner.y - ray.o.y)/ray.d.y;
    } else {
	    yfar = (minCorner.y - ray.o.y)/ray.d.y;
	    ynear = (maxCorner.y - ray.o.y)/ray.d.y;
    }
    if (ray.d.z >= 0){
 	    znear = (minCorner.z - ray.o.z)/ray.d.z;
	    zfar = (maxCorner.z - ray.o.z)/ray.d.z;
    } else {
    	zfar = (minCorner.z - ray.o.z)/ray.d.z;
	    znear = (maxCorner.z - ray.o.z)/ray.d.z;
    }    

    float maxNear = max(xnear,ynear,znear);
    float minfar = min(xfar,yfar,zfar);

    std::cout << "Nears: (" << xnear << ", " << ynear << ", " << znear << ")" << std::endl;
	std::cout << "Fars: (" << xfar << ", " << yfar << ", " << zfar << ")" << std::endl;

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
