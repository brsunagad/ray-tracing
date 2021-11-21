#include <rt/bbox.h>

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
        return std::make_pair(-INFINITY, INFINITY);
    else if (isEmpty)
        return std::make_pair(INFINITY, -INFINITY);
}

bool BBox::isUnbound() const {
    if ((min.x == -INFINITY && max.x == INFINITY) || (min.y == -INFINITY && max.y == INFINITY) || (min.z == -INFINITY && max.z == INFINITY))
        return true;
    else return false;
}

}