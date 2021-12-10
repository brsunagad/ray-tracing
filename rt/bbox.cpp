#include <cfloat>
#include <rt/bbox.h>
#include <rt/solids/aabox.h>
#include <tuple>

namespace rt {

BBox BBox::empty() {
    return BBox(true, false);
}

BBox BBox::full() {
    return BBox(false, true);
}


void BBox::extend(const Point& point) {
    if (isEmpty) {
        isEmpty = false;
        min = point;
        max = point;
    }
    else {
        min.x = std::min(point.x, min.x);
        min.y = std::min(point.y, min.y);
        min.z = std::min(point.z, min.z);
        max.x = std::max(point.x, max.x);
        max.y = std::max(point.y, max.y);
        max.z = std::max(point.z, max.z);
    }
}

void BBox::extend(const BBox& bbox) {
    if (isEmpty) {
        isEmpty = false;
        min = bbox.min;
        max = bbox.max;
    }
    else {
        min.x = std::min(bbox.min.x, min.x);
        min.y = std::min(bbox.min.y, min.y);
        min.z = std::min(bbox.min.z, min.z);
        max.x = std::max(bbox.max.x, max.x);
        max.y = std::max(bbox.max.y, max.y);
        max.z = std::max(bbox.max.z, max.z);
    }
}

std::pair<float, float> BBox::intersect(const Ray& ray) const {
    if (isFull)
        return std::make_pair(-FLT_MAX, FLT_MAX);
    else if (isEmpty)
        return std::make_pair(FLT_MAX, -FLT_MAX);
    else {
        AABox aabox(min, max, nullptr, nullptr);

        //Compute intersection
        float xnear, xfar, ynear, yfar, znear, zfar;
        float invdx = 1.0f/ray.d.x;
        float invdy = 1.0f/ray.d.y;
        float invdz = 1.0f/ray.d.z;

        // if the ray goes in negative direction, far and near are changed
        if (invdx >= 0){
            xnear = (min.x - ray.o.x)*invdx;
            xfar = (max.x - ray.o.x)*invdx;
        } else {
            xfar = (min.x - ray.o.x)*invdx;
            xnear = (max.x - ray.o.x)*invdx;
        }
        if (invdy >= 0){
            ynear = (min.y - ray.o.y)*invdy;
            yfar = (max.y - ray.o.y)*invdy;
        } else {
            yfar = (min.y - ray.o.y)*invdy;
            ynear = (max.y - ray.o.y)*invdy;
        }
        if (invdz >= 0){
            znear = (min.z - ray.o.z)*invdz;
            zfar = (max.z - ray.o.z)*invdz;
        } else {
            zfar = (min.z - ray.o.z)*invdz;
            znear = (max.z - ray.o.z)*invdz;
        }

        float maxNear;
        float minfar;

        // Try intersection on xy plane
        if ((xnear > yfar) || (ynear > xfar)) 
            return std::make_pair(FLT_MAX, -FLT_MAX); //miss
        maxNear = std::max(xnear, ynear);
        minfar = std::min(xfar, yfar);

        // Try intersection on prev and z plane
        if ((maxNear > zfar) || (znear > minfar)) 
            return std::make_pair(FLT_MAX, -FLT_MAX); //miss
        maxNear = std::max(maxNear, znear);
        minfar = std::min(minfar, zfar);

        // Hit
        return std::make_pair(maxNear, minfar);
    }
}

bool BBox::isUnbound() const {
    if ((min.x == -FLT_MAX || max.x == FLT_MAX) || (min.y == -FLT_MAX || max.y == FLT_MAX) || (min.z == -FLT_MAX || max.z == FLT_MAX))
        return true;
    else
        return false;
}

}