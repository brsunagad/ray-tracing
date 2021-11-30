#include <rt/cameras/perspective.h>
#include <cmath>
namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
{
    this->center = center;
    this->forward = forward.normalize();
    this->up = up.normalize();
    this->verticalOpeningAngle = verticalOpeningAngle;
    this->horizontalOpeningAngle = horizontalOpeningAngle;
    this->u = cross(forward, up).normalize();
    this->v = cross(u, forward).normalize();
    this->sx = tan(horizontalOpeningAngle / 2);//calculate x-scale
    this->sy = tan(verticalOpeningAngle / 2);//calculate y-scale
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
 
    return Ray(center, (forward + u * sx * x + v * sy * y).normalize());
}

}
