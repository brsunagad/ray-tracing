#include <rt/textures/checkerboard.h>
#include <cmath>
namespace rt {

CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black): white(white), black(black)
{}

RGBColor CheckerboardTexture::getColor(const Point& coord) {
	int parity = int(floor(2.0f*coord.x)+ floor(2.0f *coord.y)+ floor(2.0f *coord.z)) % 2;
	if (parity == 0)
    	return white;
    else
    	return black;
}

RGBColor CheckerboardTexture::getColorDX(const Point& coord) {
    //Find the color for x slightly bigger and smaller and calculate the difference:
    RGBColor ColorPos = getColor(Point(coord.x+0.001, coord.y, coord.z));
    RGBColor ColorNeg = getColor(Point(coord.x-0.001, coord.y, coord.z));
    return ColorPos-ColorNeg/0.002;
}

RGBColor CheckerboardTexture::getColorDY(const Point& coord) {
    //Find the color for y slightly bigger and smaller and calculate the difference:
    RGBColor ColorPos = getColor(Point(coord.x, coord.y+0.001, coord.z));
    RGBColor ColorNeg = getColor(Point(coord.x, coord.y-0.001, coord.z));
    return ColorPos-ColorNeg/0.002;
}

}