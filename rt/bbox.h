#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <utility>
#include <core/point.h>
#include <core/vector.h>

namespace rt {

class Ray;

class BBox {
private:
    bool isEmpty, isFull;

public:
    Point min, max;

    BBox() {}
    BBox(const Point& min, const Point& max): min(min), max(max), isEmpty(false), isFull(false) {}
    BBox(bool isEmpty, bool isFull): isEmpty(isEmpty), isFull(isFull){
        if (isFull) {
            min.x = -INFINITY;
            min.y = -INFINITY;
            min.z = -INFINITY;
            max.x = INFINITY;
            max.y = INFINITY;
            max.z = INFINITY;
        }
    }

    static BBox empty();
    static BBox full();

    void extend(const Point& point);
    void extend(const BBox& bbox);

    Vector diagonal() const {
        return max - min;
    }

    float area() const {
        float l = max.x - min.x;
        float b = max.y - min.y;
        float h = max.z - min.z;

        return 2 * (l * b + b * h + h * l); 
    }

    std::pair<float, float> intersect(const Ray& ray) const;

    bool isUnbound() const;
};

}

#endif