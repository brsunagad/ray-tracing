#include <core/color.h>
#include <core/scalar.h>
#include <core/float4.h>

namespace rt {

RGBColor::RGBColor(const Float4& f4)
{
/* TODO */ NOT_IMPLEMENTED;
}

RGBColor RGBColor::operator + (const RGBColor& c) const {
    return RGBColor(r + c.r, g + c.g, b + c.b);
}

RGBColor RGBColor::operator - (const RGBColor& c) const {
    return RGBColor(r - c.r, g - c.g, b - c.b);
}

RGBColor RGBColor::operator * (const RGBColor& c) const {
    return RGBColor(r * c.r, g * c.g, b * c.b);
}

bool RGBColor::operator == (const RGBColor& c) const {
    return ((r == c.r) && (g == c.g) && (b == c.b));
}

bool RGBColor::operator != (const RGBColor& x) const {
    return (r != x.r) || (g != x.g) || (b == x.b);
}

RGBColor RGBColor::clamp() const {
    //float temp = sqrt((r * r) + (g * g) + (b * b));
    float temp = r + g + b;
    return RGBColor(r / temp, g / temp, b / temp);
}

RGBColor RGBColor::gamma(float gam) const {
    /* TODO */ NOT_IMPLEMENTED;
}

float RGBColor::luminance() const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor operator * (float scalar, const RGBColor& c) {
    return RGBColor(scalar * c.r, scalar * c.g, scalar * c.b);
}

RGBColor operator * (const RGBColor& c, float scalar) {
    return RGBColor(scalar * c.r, scalar * c.g, scalar * c.b);
}

RGBColor operator / (const RGBColor& c, float scalar) {
    return RGBColor(c.r / scalar,  c.g / scalar, c.b / scalar);
}

}
