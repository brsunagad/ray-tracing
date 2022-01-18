#include <core/color.h>
#include <core/scalar.h>
#include <core/float4.h>
#include <algorithm> 

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
    
    float red=r, blue=b, green=g;

    if (r > 1.f) red = 1.f;
    else if (r < 0.f)red = 0.f;

    if (g > 1.f)green = 1.f;
    else if (g < 0.f)green = 0.f;

    if (b > 1.f)blue = 1.f;
    else if (b < 0.f)blue = 0.f;

    return RGBColor(red, green, blue);
}

RGBColor RGBColor::gamma(float gam) const {
    /* TODO */ NOT_IMPLEMENTED;
}

float RGBColor::luminance() const {
    return 0.2126*r + 0.7152*g + 0.0722*b;
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
