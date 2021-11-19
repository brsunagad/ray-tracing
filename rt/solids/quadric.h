#include <rt/solids/solid.h>

namespace rt {

    class Quadric : public Solid {
    private:
        Point center;
        float A, B, C, D, E, F, G, H, I, J;

    public:
        Quadric() {}
        Quadric(const Point& center, const float& A, const float& B, const float& C, const float& D, const float& E, const float& F, const float& G,
        const float& H, const float& I, const float& J, CoordMapper* texMapper, Material* material);

        virtual BBox getBounds() const;
        virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
        virtual Sample sample() const;
        virtual float getArea() const;
       
    };

}
