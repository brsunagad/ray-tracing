#include <rt/cameras/orthographic.h>
#include <rt/ray.h>

namespace rt {

OrthographicCamera::OrthographicCamera(const Point& center, const Vector& forward, const Vector& up, float scaleX, float scaleY)
{
    this->center = center;
    this->forward = forward;
    this-> up = up;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->w = -forward.normalize();
    this->u = cross(up, w).normalize();
    this->v = cross(w, u).normalize();
}

Ray OrthographicCamera::getPrimaryRay(float x, float y) const {
    
    return Ray(center + scaleX/2 * x * u + scaleY/2 * y * v, -w) ;
}

}
