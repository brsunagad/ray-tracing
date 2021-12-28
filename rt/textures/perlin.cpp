#include <rt/textures/perlin.h>

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
    if (octaves.size() == 0) octaves.push_back(std::make_pair(1.0f,1.0f));
    RGBColor finalColor = RGBColor::rep(0.0f);
    for (auto o : octaves){
        //We obtain [-1,1] we change it to [0,1] 
        float noiseNorm = noise(coord.x*o.second, coord.y*o.second, coord.z*o.second)/2.0f + 0.5f;
        finalColor = finalColor + o.first*(white * noiseNorm + black * (1-noiseNorm));
    }
    return finalColor;
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