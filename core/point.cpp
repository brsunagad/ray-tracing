#include <core/point.h>
#include <core/float4.h>
#include <core/scalar.h>
#include <core/assert.h>
#include <core/vector.h>

namespace rt {

Point::Point(float x, float y, float z):
    x(x), y(y), z(z) {}

Point::Point(const Float4& f4):
    x(f4.x / f4.w), y(f4.y / f4.w), z(f4.z / f4.w) {}

Vector Point::operator - (const Point& b) const {
    return Vector(x - b.x, y - b.y, z - b.z);
}

bool Point::operator == (const Point& b) const {
    return ((x == b.x) && (y == b.y) && (z == b.z));
}

bool Point::operator != (const Point& b) const {
    return !((x == b.x) && (y == b.y) && (z == b.z));
}

Point operator * (float scalar, const Point& b) {
    return Point(scalar * b.x, scalar * b.y, scalar * b.z);
}

Point operator * (const Point& a, float scalar) {
    return Point(scalar * a.x, scalar * a.y, scalar * a.z);
}

Point min(const Point& a, const Point& b) {
    return Point(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z));
}

Point max(const Point& a, const Point& b) {
    return Point(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z));
}

}
