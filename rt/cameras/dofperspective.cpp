#include <rt/cameras/dofperspective.h>
#include <rt/ray.h>
#include <core/random.h>
#include <cmath>

namespace rt {

DOFPerspectiveCamera::DOFPerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle, float focalDistance, float apertureRadius):
    center(center),
    forward(forward),
    up(up),
    apertureRadius(apertureRadius),
    focalDistance(focalDistance),
    scaleX(tan(horizontalOpeningAngle / 2)),
    scaleY(tan(verticalOpeningAngle / 2)),
    spanX(cross(forward, up).normalize()),
    spanY(cross(spanX, forward).normalize()){}

Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const {
//source: https://medium.com/@elope139/depth-of-field-in-path-tracing-e61180417027

    Vector direction = forward + x * spanX * scaleX + y * spanY * scaleY;
    Point focalPoint = center + focalDistance * direction;
    Point randomRayOrigin = center + (random() - 0.5f) * apertureRadius * spanX + (random() - 0.5f) * apertureRadius * spanY;//random number[-0.5 0.5]
    Vector rayDirection = (focalPoint - randomRayOrigin).normalize();
    return Ray(randomRayOrigin, rayDirection);
}

}