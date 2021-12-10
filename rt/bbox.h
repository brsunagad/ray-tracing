#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <cfloat>
#include <utility>
#include <core/point.h>
#include <core/vector.h>
#include <tuple>


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
        if (isEmpty) {
            min = Point::rep(FLT_MAX);
            max = Point::rep(-FLT_MAX);
        }
        if (isFull) {
            min = Point::rep(-FLT_MAX);
            max = Point::rep(FLT_MAX);
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