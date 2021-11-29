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
        Intersection intersect = aabox.intersect(ray, FLT_MAX);//passing infinity as previousbest distance 
        if (intersect) {
            float t1, t2;
            Vector normal;
            std::tie(t1, t2, normal) = aabox.getIntersectionValues();
            return std::make_pair(t1, t2);
        }
        else
            return std::make_pair(FLT_MAX, -FLT_MAX); // t2>t1 is checked in finding AABox intersection
    }
}

bool BBox::isUnbound() const {
    if ((min.x == -FLT_MAX && max.x == FLT_MAX) || (min.y == -FLT_MAX && max.y == FLT_MAX) || (min.z == -FLT_MAX && max.z == FLT_MAX))
        return true;
    else
        return false;
}

}