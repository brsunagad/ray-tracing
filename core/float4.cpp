#include <core/float4.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/assert.h>
#include <core/scalar.h>

namespace rt {

Float4::Float4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}

Float4::Float4(const Point& p): x(p.x), y(p.y), z(p.z), w(1.0f) {}

Float4::Float4(const Vector& vec): x(vec.x), y(vec.y), z(vec.z), w(0.0f) {}

float& Float4::operator [] (int idx) {
    if (idx == 0) return x;
    else if (idx == 1) return y;
    else if (idx == 2) return z;
    else if (idx == 3) return w;
}

float Float4::operator [] (int idx) const {
    if (idx == 0) return x;
    else if (idx == 1) return y;
    else if (idx == 2) return z;
    else if (idx == 3) return w;
}

Float4 Float4::operator + (const Float4& b) const {
    return Float4(x + b.x,  y +b.y, z + b.z, w + b.w);
}

Float4 Float4::operator - (const Float4& b) const {
    return Float4(x - b.x, y - b.y, z - b.z, w - b.w);
}

Float4 Float4::operator * (const Float4& b) const {
    return Float4(x * b.x, y * b.y, z * b.z, w * b.w);
}

Float4 Float4::operator / (const Float4& b) const {
    return Float4(x / b.x, y / b.y, z / b.z, w / b.w);
}

Float4 operator * (float scalar, const Float4& b) {
    return Float4(scalar * b.x, scalar * b.y, scalar * b.z, scalar * b.w);
}

Float4 operator * (const Float4& a, float scalar) {
    return Float4(scalar * a.x, scalar * a.y, scalar * a.z, scalar * a.w);
}

Float4 operator / (const Float4& a, float scalar) {
    return Float4(a.x / scalar, a.y / scalar, a.z / scalar, a.w / scalar);
}

float dot(const Float4& a, const Float4& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Float4 Float4::operator - () const {
    return Float4(-x, -y, -z, -w);
}

bool Float4::operator == (const Float4& b) const {
    return ((x == b.x) && (y == b.y) && (z == b.z) && (w == b.w));
}

bool Float4::operator != (const Float4& b) const {
    return !((x == b.x) && (y == b.y) && (z == b.z) && (w == b.w));
}

Float4 min(const Float4& a, const Float4& b) {
    return Float4(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w));
}

Float4 max(const Float4& a, const Float4& b) {
    return Float4(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w));
}

}