#include <core/scalar.h>
#include <core/image.h>
#include <rt/renderer.h>
#include <rt/ray.h>
#include <iostream>
#include <rt/cameras/camera.h>
#include <omp.h>

namespace rt {

Renderer::Renderer(Camera* cam, Integrator* integrator)
    : cam(cam), integrator(integrator), samples(1)
{}

void Renderer::render(Image& img) {
    img.clear(RGBColor(0, 0, 0));
    float ndcx, ndcy, sscx, sscy;
    uint k;
    const uint height = img.height();
    const uint width = img.width();

    const float sx = 2.0 / width;
    const float sy = 2.0 / height;

    std::cout << std::endl << "Rendering with " << samples << " samples..." << std::endl << std::endl;

#pragma omp parallel for
//#pragma omp parallel for collapse(2) schedule(dynamic)
    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
            //if (i%100 == 0 && j==0) std::cout << "pixel (" << i << ", " << j << ")" <<std::endl;

            if (samples > 1) { //Super sampling
                RGBColor pixel = RGBColor::rep(0);
                for (int k = 0; k < samples; ++k) {
                    // Random hitpoint inside the pixel
                    ndcx = (i + random());
                    ndcy = (j + random());

                    // Screen space coordinates [-1, 1]
                    //sscx = ndcx * 2 - 1;
                    //sscy = 1- ndcy * 2;
                    sscx = ndcx * sx - 1.0;
                    sscy = 1.0 - ndcy * sy;

                    pixel = pixel + integrator->getRadiance(cam->getPrimaryRay(sscx,sscy));
                }
                img(i,j) = pixel / samples;
            } else {
                // Normalized device coordinates [0, 1]
                ndcx = (i + 0.5);
                ndcy = (j + 0.5);

                // Screen space coordinates [-1, 1]
                sscx = ndcx * sx - 1;
                sscy = 1- ndcy * sy;

                img(i,j) = integrator->getRadiance(cam->getPrimaryRay(sscx,sscy));
            }
        }
    }
}
}

rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);

namespace rt {

void Renderer::test_render1(Image& img) {
    img.clear(RGBColor(0,0,0));

    for (uint i = 0; i < img.width(); i++) {
        for (uint k = 0; k < img.height(); k++) {
            img(i, k) =  a1computeColor(i, k, img.width(), img.height());
        }
    }
}
}

rt::RGBColor a2computeColor(const rt::Ray& r);

namespace rt {

void Renderer::test_render2(Image& img) {
    img.clear(RGBColor(0, 0, 0));

    for (uint i = 0; i < img.width(); i++) {
        for (uint j = 0; j < img.height(); j++) {

            // Normalized device coordinates [0, 1]
            float ndcx = (i + 0.5) / img.width();
            float ndcy = (j + 0.5) / img.height();

            // Screen space coordinates [-1, 1]
            float sscx = ndcx * 2 - 1;
            float sscy = 1- ndcy * 2;

            img(i,j)= a2computeColor(cam->getPrimaryRay(sscx,sscy));
        }
    }
}

}
