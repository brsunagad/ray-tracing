#include <core/scalar.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/float4.h>
#include <core/assert.h>
#include <algorithm>
#include <cmath>

namespace rt {

Vector::Vector(float x, float y, float z):
    x(x), y(y), z(z) {}

Vector::Vector(const Float4& f4): x(f4.x), y(f4.y), z(f4.z) 
{
    assert(f4.w == 0);
}

Vector Vector::operator + (const Vector& b) const {
   return Vector(x + b.x, y + b.y, z + b.z);
}

Vector Vector::operator - (const Vector& b) const {
    return Vector(x - b.x, y - b.y, z - b.z);
}

Vector Vector::operator - () const {  
    return Vector(-x, -y, -z);
}

Vector Vector::normalize() const {    
    return Vector(x / length(), y / length(), z / length());
}

Vector operator * (float scalar, const Vector& b) {   
    return Vector(scalar * b.x, scalar * b.y, scalar * b.z);
}

Vector operator * (const Vector& a, float scalar) {    
    return Vector(scalar * a.x, scalar * a.y, scalar * a.z);
}

Vector operator / (const Vector& a, float scalar) {   
    Vector vec;
    vec.x = a.x / scalar; vec.y = a.y / scalar; vec.z = a.z / scalar;
    
    return vec;
}

Vector cross(const Vector& a, const Vector& b) {   
    return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

float dot(const Vector& a, const Vector& b) {
    return a.x*b.x + a.y * b.y+ a.z * b.z;
}

float Vector::lensqr() const {
    return (float)pow(length(),2);
}

float Vector::length() const {
    return sqrt((x * x) + (y * y) + (z * z));
}


bool Vector::operator == (const Vector& b) const {
    return ((x==b.x) && (y==b.y) && (z==b.z));
}

bool Vector::operator != (const Vector& b) const {
    return !((x == b.x) && (y == b.y) && (z == b.z));
}

Vector min(const Vector& a, const Vector& b) {
    return Vector(min(a.x,b.x), min(a.y, b.y), min(a.z, b.z));
}

Vector max(const Vector& a, const Vector& b) {
    return Vector(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z));
}

Point operator + (const Point& a, const Vector& b) {
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point operator + (const Vector& a, const Point& b) {
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point operator - (const Point& a, const Vector& b) {
    return Point(a.x - b.x, a.y - b.y, a.z - b.z);
}

Point operator * (const Float4& scale, const Point& p) {
    return Point(scale.w * p.x, scale.w * p.y , scale.w * p.z);
}

}
