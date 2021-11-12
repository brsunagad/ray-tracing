#include <rt/cameras/perspective.h>
#include <cmath>
namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
{
    this->center = center;
    this->forward = forward;
    this->up = up;
    this->verticalOpeningAngle = verticalOpeningAngle;
    this->horizontalOpeningAngle = horizontalOpeningAngle;
    this->w = -forward.normalize();
    this->u = cross(up, w).normalize();
    this->v = cross(w, u).normalize();
    this->sx = forward.length() * tan(horizontalOpeningAngle / 2);//calculate x-scale
    this->sy = forward.length() * tan(verticalOpeningAngle / 2);//calculate y-scale
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
   

    return Ray(center, (forward + u * sx * x + v * sy * y).normalize());
}

}
