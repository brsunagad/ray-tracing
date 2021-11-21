#ifndef CG1RAYTRACER_SOLIDS_BOX_HEADER
#define CG1RAYTRACER_SOLIDS_BOX_HEADER

#include <rt/solids/solid.h>
#include <tuple>

namespace rt {

class AABox : public Solid {
public:
    AABox() {}
    AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual Sample sample() const;
    virtual float getArea() const;
    void setIntersectionValues(float t1, float t2, Vector& normal) const ;
    std::tuple<float, float, Vector> getIntersectionValues() const;
private:
	Point maxCorner;
	Point minCorner;
    mutable float t1, t2;
    mutable Vector _normal;
};

}

#endif