#ifndef CG1RAYTRACER_CAMERAS_PERSPECTIVE_HEADER
#define CG1RAYTRACER_CAMERAS_PERSPECTIVE_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>

namespace rt {

class PerspectiveCamera : public Camera {
public:
    Point center;
    Vector u, v, up, forward;
    float verticalOpeningAngle, sy;
    float horizontalOpeningAngle, sx;

    PerspectiveCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle
        );

    virtual Ray getPrimaryRay(float x, float y) const;
};

}


#endif