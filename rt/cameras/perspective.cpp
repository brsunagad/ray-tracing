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
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
   
    float sx = forward.length() *tan(horizontalOpeningAngle/2);
    float sy = forward.length()*tan(verticalOpeningAngle/2);
    //return Ray(center, (Point(x*sx*u.x , y*sy*u.y, -1) - center).normalize());
    return Ray(center, (forward + u * sx * x + v * sy * y).normalize());
}

}
