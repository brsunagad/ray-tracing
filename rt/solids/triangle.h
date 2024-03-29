#ifndef CG1RAYTRACER_SOLIDS_TRIANGLE_HEADER
#define CG1RAYTRACER_SOLIDS_TRIANGLE_HEADER

#include <rt/solids/solid.h>

namespace rt {

class Triangle : public Solid {
private:
    Point v1, v2, v3;
    Vector v1v2, v1v3, normal;

public:
    Triangle() {}
    Triangle(Point vertices[3], CoordMapper* texMapper, Material* material);
    Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual Sample sample() const;
    virtual float getArea() const;
    Point getBaryCentricCoordinates(const Point& p) const;
    Vector getVectoru() { return v1v2; };
    Vector getVectorv() { return v1v3; };
};

}

#endif