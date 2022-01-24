#include <core/scalar.h>
#include <core/image.h>
#include <rt/renderer.h>
#include <rt/ray.h>
#include <iostream>
#include <rt/cameras/camera.h>


namespace rt {

Renderer::Renderer(Camera* cam, Integrator* integrator)
    : cam(cam), integrator(integrator), samples(1)
{}

void Renderer::render(Image& img) {
    img.clear(RGBColor(0, 0, 0));
    float ndcx, ndcy, sscx, sscy;
    uint k;


 #pragma omp parallel for collapse(2) schedule(dynamic)  
    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
            // if (j%100 == 0) std::cout << "pixel (" << i << ", " << j << ")" <<std::endl;

            if (samples > 1) { //Super sampling
                k = samples;
                while (k-- > 0) {
                    // Random hitpoint inside the pixel
                    ndcx = (i + random()) / img.width();
                    ndcy = (j + random()) / img.height();

                    // Screen space coordinates [-1, 1]
                    sscx = ndcx * 2 - 1;
                    sscy = 1- ndcy * 2;

                    img(i,j) = img(i,j) + integrator->getRadiance(cam->getPrimaryRay(sscx,sscy))/samples;
                }
            } else {
                // Normalized device coordinates [0, 1]
                ndcx = (i + 0.5) / img.width();
                ndcy = (j + 0.5) / img.height();

                // Screen space coordinates [-1, 1]
                sscx = ndcx * 2 - 1;
                sscy = 1- ndcy * 2;

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
