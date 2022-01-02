#include <rt/textures/imagetex.h>

namespace rt {

ImageTexture::ImageTexture(){}

ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i): bh(bh), i(i)
{
    Image image;
    image.readPNG(filename);
    img = image;
}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i) : bh(bh), i(i), img(image) {}

RGBColor ImageTexture::getColor(const Point& coord) {
    int floorX = floor(coord.x);
    int floorY = floor(coord.y);

    float tu, tv;
    switch (bh) {
    case ImageTexture::CLAMP:
    	//we multiply by a value slightly less than 1 to prevent out of bounds index when calculating floor
        tu = coord.x < 0 ? 0.0f : coord.x;
        tu = coord.x > 1 ? 1.0f : tu;
        tv = coord.y < 0 ? 0.0f : coord.y;
        tv = coord.y > 1 ? 1.0f : tv;
        break;

    case ImageTexture::MIRROR:
        tu = coord.x - floorX;
        tv = coord.y - floorY;
        if (abs(floorX) % 2 == 1) { tu = 1 - tu; }
        if (abs(floorY) % 2 == 1) { tv = 1 - tv; }
        break;

    default: //repeat
        tu = coord.x - floorX;
        tv = coord.y - floorY;
        break;
    }

    float resU = img.width();
    float resV = img.height();

    float u, v, lu, lv;

    if (i == ImageTexture::NEAREST) {

        u = tu * resU;
        v = tv * resV;

        lu = std::fmin(floor(u), resU - 1.0f);
        lv = std::fmin(floor(v), resV - 1.0f);

        return img(lu, lv);
    }
    else { //bilinear
        u = tu * (1-epsilon) * (resU - 1.0f);
        v = tv * (1-epsilon) * (resV - 1.0f);

        int flru = floor(u);
        int flrv = floor(v);

        lu = u - flru;
        lv = v - flrv;

        return (
            (1 - lu) * (1 - lv) * img(flru, flrv) +
            (1 - lu) * lv * img(flru, flrv + 1) +
            lu * (1 - lv) * img(flru + 1, flrv) +
            lu * lv * img(flru + 1, flrv + 1)
            );
    }

}

RGBColor ImageTexture::getColorDX(const Point& coord) {
    //Find the color for x slightly bigger and smaller and calculate the difference:
    RGBColor ColorPos = getColor(Point(coord.x+0.001, coord.y, coord.z));
    RGBColor ColorNeg = getColor(Point(coord.x-0.001, coord.y, coord.z));
    return (ColorPos-ColorNeg)/0.002;
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
    //Find the color for y slightly bigger and smaller and calculate the difference:
    RGBColor ColorPos = getColor(Point(coord.x, coord.y+0.001, coord.z));
    RGBColor ColorNeg = getColor(Point(coord.x, coord.y-0.001, coord.z));
    return (ColorPos-ColorNeg)/0.002;
}

}