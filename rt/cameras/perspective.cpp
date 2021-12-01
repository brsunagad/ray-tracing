#include <rt/cameras/perspective.h>
#include <cmath>
namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle):
    center(center), forward(forward.normalize()), up(up.normalize()),
    verticalOpeningAngle(verticalOpeningAngle), horizontalOpeningAngle(horizontalOpeningAngle),
    u(cross(forward, up).normalize()), v(cross(u, forward).normalize()),
    sx(tan(horizontalOpeningAngle / 2)), sy(tan(verticalOpeningAngle / 2))
{
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
   
    return Ray(center, (forward + u * sx * x + v * sy * y).normalize());
}

}
