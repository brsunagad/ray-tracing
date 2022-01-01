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

    default:
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
    else {
        u = tu * (resU - 1.0f);
        v = tv * (resV - 1.0f);

        lu = u - floor(u);
        lv = v - floor(v);

        int flru = floor(u);
        int flrv = floor(v);

        return (
            (1 - lu) * (1 - lv) * img(flru, flrv) +
            (1 - lu) * lv * img(flru, flrv + 1) +
            lu * (1 - lv) * img(flru + 1, flrv) +
            lu * lv * img(flru + 1, flrv + 1)
            );
    }

}

RGBColor ImageTexture::getColorDX(const Point& coord) {
    // /* TODO */ NOT_IMPLEMENTED;
    return RGBColor::rep(0.0f);
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
    // /* TODO */ NOT_IMPLEMENTED;
    return RGBColor::rep(0.0f);
}

}