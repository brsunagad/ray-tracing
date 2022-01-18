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
    // float resU = img.width();
    // RGBColor ColorPos = getColor(Point(coord.x+(1.0f/resU), coord.y, coord.z));
    // RGBColor ColorNeg = getColor(Point(coord.x, coord.y, coord.z));
    // return (ColorNeg-ColorPos)/(1.0f/resU);


    int floorX = floor(coord.x);
    int floorY = floor(coord.y);

    float tu, tv;
    switch (bh) {
    case ImageTexture::CLAMP:
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

    int resU = img.width();
    int resV = img.height();

    float u, v, lu, lv;

    if (i == ImageTexture::NEAREST) {

        u = tu * resU;
        v = tv * resV;

        int flru = std::min(floor(u), resU - 1.0f);
        int flrv = std::min(floor(v), resV - 1.0f);

        return img(flru, flrv)-img((flru+1)%(resU-1), flrv);
    }
    else { //bilinear
        u = tu * (1-epsilon) * (resU - 1.0f);
        v = tv * (1-epsilon) * (resV - 1.0f);

        int flru = floor(u);
        int flrv = floor(v);

        lu = u - flru;
        lv = v - flrv;

        RGBColor Px0y0 = img(flru, flrv)-img(flru+1, flrv);
        RGBColor Px1y0 = img(flru+1, flrv)-img((flru+2)%(resU-1), flrv);
        RGBColor Px0y1 = img(flru, flrv+1)-img(flru+1, flrv+1);
        RGBColor Px1y1 = img(flru+1, flrv+1)-img((flru+2)%(resU-1), flrv+1);

        return lerp2d(Px0y0,Px1y0,Px0y1,Px1y1,lu,lv);
    }
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
    //Find the color for y slightly bigger and smaller and calculate the difference:
    // float resV = img.height();
    // RGBColor ColorPos = getColor(Point(coord.x, coord.y+(1.0f/resV), coord.z));
    // RGBColor ColorNeg = getColor(Point(coord.x, coord.y, coord.z));
    // return (ColorNeg-ColorPos)/(1.0f/resV);


    int floorX = floor(coord.x);
    int floorY = floor(coord.y);

    float tu, tv;
    switch (bh) {
    case ImageTexture::CLAMP:
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

    int resU = img.width();
    int resV = img.height();

    float u, v, lu, lv;

    if (i == ImageTexture::NEAREST) {

        u = tu * resU;
        v = tv * resV;

        int flru = std::min(floor(u), resU - 1.0f);
        int flrv = std::min(floor(v), resV - 1.0f);

        return img(flru, flrv)-img(flru, (flrv+1)%(resV-1));
    }
    else { //bilinear
        u = tu * (1-epsilon) * (resU - 1.0f);
        v = tv * (1-epsilon) * (resV - 1.0f);

        int flru = floor(u);
        int flrv = floor(v);

        lu = u - flru;
        lv = v - flrv;

        RGBColor Px0y0 = img(flru, flrv)-img(flru, flrv+1);
        RGBColor Px1y0 = img(flru+1, flrv)-img(flru+1, flrv+1);
        RGBColor Px0y1 = img(flru, flrv+1)-img(flru, (flrv+2)%(resV-1));
        RGBColor Px1y1 = img(flru+1, flrv+1)-img(flru+1, (flrv+2)%(resV-1));

        return lerp2d(Px0y0,Px1y0,Px0y1,Px1y1,lu,lv);
    }
}

}