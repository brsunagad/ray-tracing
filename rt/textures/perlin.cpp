#include <rt/textures/perlin.h>
#include <core/interpolate.h>

namespace rt {

// returns a value in range -1 to 1
static inline float noise(int x, int y, int z) {
    int n = x + y * 57 + z * 997;
    n = (n << 13) ^ n;
    return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

PerlinTexture::PerlinTexture(const RGBColor& white, const RGBColor& black): white(white), black(black)
{}

rt::RGBColor PerlinTexture::getColor(const Point& coord) {

    float interpolation = 0.0f;
    for (auto o : octaves) {
        int lu = floorf(coord.x * o.second);
        int lv = floorf(coord.y * o.second);
        int lw = floorf(coord.z * o.second);

        float wu = coord.x * o.second - lu;
        float wv = coord.y * o.second - lv;
        float ww = coord.z * o.second - lw;

        interpolation = interpolation +
            lerp3d(
                noise(lu, lv, lw),
                noise(lu + 1, lv, lw),
                noise(lu, lv + 1, lw),
                noise(lu + 1, lv + 1, lw),
                noise(lu, lv, lw + 1),
                noise(lu + 1, lv, lw + 1),
                noise(lu, lv + 1, lw + 1),
                noise(lu + 1, lv + 1, lw + 1),
                wu,
                wv,
                ww
            ) * o.first;
    }

    interpolation = (interpolation + 1) / 2;
    RGBColor color = lerp(black, white, interpolation);
    return color;
}

rt::RGBColor PerlinTexture::getColorDX(const Point& coord) {
    //Find the color for x slightly bigger and smaller and calculate the difference:
    RGBColor ColorPos = getColor(Point(coord.x+0.001, coord.y, coord.z));
    RGBColor ColorNeg = getColor(Point(coord.x-0.001, coord.y, coord.z));
    return (ColorPos-ColorNeg)/0.002;
}

rt::RGBColor PerlinTexture::getColorDY(const Point& coord) {
    //Find the color for y slightly bigger and smaller and calculate the difference:
    RGBColor ColorPos = getColor(Point(coord.x, coord.y+0.001, coord.z));
    RGBColor ColorNeg = getColor(Point(coord.x, coord.y-0.001, coord.z));
    return (ColorPos-ColorNeg)/0.002;
}

void PerlinTexture::addOctave(float amplitude, float frequency) {
    // /* TODO */ NOT_IMPLEMENTED;
    octaves.push_back(std::make_pair(amplitude,frequency));
}

}