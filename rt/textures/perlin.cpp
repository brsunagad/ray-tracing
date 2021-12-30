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
    //Iterate over all octaves, if no octave was set, we use defautl 1,1
    //if (octaves.size() == 0) octaves.push_back(std::make_pair(1.0f,1.0f));
    //RGBColor finalColor = RGBColor::rep(0.0f);
    //for (auto o : octaves){
    //    //We obtain [-1,1] we change it to [0,1] 
    //    float noiseNorm = noise(coord.x*o.second, coord.y*o.second, coord.z*o.second)/2.0f + 0.5f;
    //    finalColor = finalColor + o.first*(white * noiseNorm + black * (1-noiseNorm));
    //}
    //return finalColor;
    Point p;
    float total = 0.0f;
    int lu, lv, lw;
    float fu, fv, fw;
    float n1, n2, n3, n4, n5, n6, n7, n8;
    for (auto o : octaves) {
        p = o.second * coord;
        lu = floor(p.x); lv = floor(p.y); lw = floor(p.z);
        fu = p.x - lu; fv = p.y - lv; fw = p.z - lw;
        n1 = fabs(noise(lu, lv, lw));
        n2 = fabs(noise(lu + 1, lv, lw));
        n3 = fabs(noise(lu, lv + 1, lw));
        n4 = fabs(noise(lu + 1, lv + 1, lw));
        n5 = fabs(noise(lu, lv, lw + 1));
        n6 = fabs(noise(lu + 1, lv, lw + 1));
        n7 = fabs(noise(lu, lv + 1, lw + 1));
        n8 = fabs(noise(lu + 1, lv + 1, lw + 1));
        total = total + (lerp3d(n1, n2, n3, n4, n5, n6, n7, n8, fu, fv, fw) * o.first);
    }
    return lerp(black, white, total);
}

rt::RGBColor PerlinTexture::getColorDX(const Point& coord) {
    //Find the color for x slightly bigger and smaller and calculate the difference:
    RGBColor ColorPos = getColor(Point(coord.x+0.001, coord.y, coord.z));
    RGBColor ColorNeg = getColor(Point(coord.x-0.001, coord.y, coord.z));
    return ColorPos-ColorNeg/0.002;
}

rt::RGBColor PerlinTexture::getColorDY(const Point& coord) {
    //Find the color for y slightly bigger and smaller and calculate the difference:
    RGBColor ColorPos = getColor(Point(coord.x, coord.y+0.001, coord.z));
    RGBColor ColorNeg = getColor(Point(coord.x, coord.y-0.001, coord.z));
    return ColorPos-ColorNeg/0.002;
}

void PerlinTexture::addOctave(float amplitude, float frequency) {
    // /* TODO */ NOT_IMPLEMENTED;
    octaves.push_back(std::make_pair(amplitude,frequency));
}

}