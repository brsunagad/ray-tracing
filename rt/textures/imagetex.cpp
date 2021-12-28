#include <rt/textures/imagetex.h>

namespace rt {

ImageTexture::ImageTexture()
{
    /* TODO */
}

ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i)
{
    /* TODO */
}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i)
{
    /* TODO */
}

RGBColor ImageTexture::getColor(const Point& coord) {
    // /* TODO */ NOT_IMPLEMENTED;
    return RGBColor::rep(0.0f);

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