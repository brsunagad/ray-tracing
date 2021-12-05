#include <core/float4.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/assert.h>
#include <core/scalar.h>

namespace rt {

Float4::Float4(float x, float y, float z, float w) {
    /* TODO */
}

Float4::Float4(const Point& p) {
    /* TODO */ NOT_IMPLEMENTED;
}

Float4::Float4(const Vector& vec) {
    /* TODO */ NOT_IMPLEMENTED;
}

float& Float4::operator [] (int idx) {
    /* TODO */ NOT_IMPLEMENTED;
}

float Float4::operator [] (int idx) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Float4 Float4::operator + (const Float4& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Float4 Float4::operator - (const Float4& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Float4 Float4::operator * (const Float4& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Float4 Float4::operator / (const Float4& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Float4 operator * (float scalar, const Float4& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Float4 operator * (const Float4& a, float scalar) {
    /* TODO */ NOT_IMPLEMENTED;
}

Float4 operator / (const Float4& a, float scalar) {
    /* TODO */ NOT_IMPLEMENTED;
}

float dot(const Float4& a, const Float4& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Float4 Float4::operator - () const {
    /* TODO */ NOT_IMPLEMENTED;
}

bool Float4::operator == (const Float4& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

bool Float4::operator != (const Float4& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Float4 min(const Float4& a, const Float4& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Float4 max(const Float4& a, const Float4& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

}