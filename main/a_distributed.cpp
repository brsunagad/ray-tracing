
#include <core/image.h>
#include <core/color.h>
#include <rt/world.h>
#include <rt/groups/simplegroup.h>
#include <rt/cameras/perspective.h>
#include <rt/cameras/dofperspective.h>
#include <rt/textures/constant.h>
#include <rt/renderer.h>
#include <rt/integrators/recraytrace.h>
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/glass.h>
#include <rt/materials/fuzzymirror.h>
#include <rt/lights/arealight.h>
#include <rt/lights/pointlight.h>
#include <rt/textures/imagetex.h>
#include <rt/primmod/animatedprimitive.h>
#include <rt/materials/combine.h>
#include <rt/coordmappers/coordmapper.h>

#include <rt/materials/phong.h>
#include <rt/materials/glass.h>
#include <rt/materials/mirror.h>
#include <rt/materials/flatmaterial.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/combine.h>
#include <rt/textures/perlin.h>
using namespace rt;

namespace {

    class QuadMapper : public CoordMapper {
    public:
        QuadMapper(const Vector& offset, const Vector& scale = Vector::rep(1.f)) : offset(offset), scale(scale) { }
        virtual Point getCoords(const Intersection& hit) const {
            Float4 p = Float4(scale) * Float4(hit.local()) + Float4(offset);
            return Point(p[0], p[1], p[2]);
        }

    private:
        Vector offset;
        Vector scale;
    };

void makeBox(Group* scene, const Point& aaa, const Vector& forward, const Vector& left, const Vector& up, CoordMapper* texMapper, Material* material) {
    scene->add(new Quad(aaa, left, forward, texMapper, material));
    scene->add(new Quad(aaa, forward, up, texMapper, material));
    scene->add(new Quad(aaa, up, left, texMapper, material));
    Point bbb = aaa + forward + left + up;
    scene->add(new Quad(bbb, -forward, -left, texMapper, material));
    scene->add(new Quad(bbb, -up, -forward, texMapper, material));
    scene->add(new Quad(bbb, -left, -up, texMapper, material));
}


void renderCornellbox(float scale, const char* filename, Camera* cam, Material* sphereMaterial, Material* floorMaterial, int numSamples=1) {
    Image img(400, 400);
    World world;
    SimpleGroup* scene = new SimpleGroup();
    world.scene = scene;

    Texture* redtex = new ConstantTexture(RGBColor(.7f,0.f,0.f));
    Texture* greentex = new ConstantTexture(RGBColor(0.f,.7f,0.f));
    Texture* yellowtex = new ConstantTexture(RGBColor(0.7f,.7f,0.f));
    Texture* bluetex = new ConstantTexture(RGBColor(0.f,0.f,0.7f));
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));

    Material* grey = new LambertianMaterial(blacktex, whitetex);
    Material* yellowmat = new LambertianMaterial(blacktex, yellowtex);
    Material* leftWallMaterial = new LambertianMaterial(blacktex, redtex);
    Material* rightWallMaterial = new LambertianMaterial(blacktex, greentex);
    
    
    

    //walls
    scene->add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(550.f, 000.f, 000.f)*scale, nullptr, floorMaterial)); //floor
   // scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(-550.f, 000.f, 000.f)*scale, nullptr, grey)); //ceiling
    scene->add(new Quad(Point(000.f, 000.f, 560.f)*scale, Vector(000.f, 550.f, 000.f)*scale, Vector(550.f, 000.f, 000.f)*scale, nullptr, grey)); //back wall
    scene->add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(000.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, nullptr, rightWallMaterial)); //right wall
    scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, -550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, nullptr, leftWallMaterial)); //left wall

    scene->add(new Sphere(Point(150.0f, 100.0f, 240.0f)*scale, 99.0f*scale, nullptr, sphereMaterial));
    scene->add(new Sphere(Point(450.0f, 50.0f, 50.0f)*scale, 49.0f*scale, nullptr, yellowmat));

    //tall box
    makeBox(scene, Point(265.f, 000.1f, 296.f)*scale, Vector(049.f, 000.f, 160.f)*scale, Vector(158.f, 000.f, -049.f)*scale, Vector(000.f, 330.f, 000.f)*scale, nullptr, grey);

    //Lights
    ConstantTexture* lightsrctex = new ConstantTexture(RGBColor::rep(35.0f));
    ImageTexture* imgtex = new ImageTexture("models/environmentMap2.png");
    Material* lightsource = new LambertianMaterial(imgtex, blacktex);
   // Material* lightsource = new  PhongMaterial(imgtex, 1.0f);
    CombineMaterial* combined = new CombineMaterial();
    //combined->add(new PhongMaterial(perlinTex, 10.0f), 0.62f);
    combined->add(lightsource, 2.0f);
    combined->add(new MirrorMaterial(0.0f, 0.0f), 0.50f);
    //combined->add(new FlatMaterial(fire), 0.2);
    //combined->add(new  GlassMaterial(1.5f, nullptr), 0.8f);
    CoordMapper* mapper = new QuadMapper(Vector::rep(-1.f), Vector::rep(1.0f));
    Quad* light = new Quad(Point(550.f, 550.f, 000.f) * scale, Vector(000.f, 000.f, 560.f) * scale, Vector(-550.f, 000.f, 000.f) * scale, mapper, combined);
    AreaLight als(light, 2);
    world.light.push_back(&als);
    scene->add(light);

    //point light
   // world.light.push_back(new PointLight(Point(490*scale,159.99f*scale,279.5f*scale),RGBColor(40000.0f*scale*scale,0,0)));
   // world.light.push_back(new PointLight(Point(40*scale,159.99f*scale,249.5f*scale),RGBColor(5000.0f*scale*scale,30000.0f*scale*scale,5000.0f*scale*scale)));

    RecursiveRayTracingIntegrator integrator(&world, 6);

    Renderer engine(cam, &integrator);
    if (numSamples>1)
        engine.setSamples(numSamples);
    engine.render(img);
    img.writePNG(filename);
}


void renderMotionBlurr(float scale, const char* filename, Camera* cam, Material* sphereMaterial, Material* floorMaterial, int numSamples=1) {
    Image img(400, 400);
    World world;
    SimpleGroup* scene = new SimpleGroup();
    world.scene = scene;

    Texture* redtex = new ConstantTexture(RGBColor(.7f,0.f,0.f));
    Texture* greentex = new ConstantTexture(RGBColor(0.f,.7f,0.f));
    Texture* yellowtex = new ConstantTexture(RGBColor(0.7f,.7f,0.f));
    Texture* bluetex = new ConstantTexture(RGBColor(0.f,0.f,0.7f));
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));

    Material* grey = new LambertianMaterial(blacktex, whitetex);
    Material* yellowmat = new LambertianMaterial(blacktex, yellowtex);
    Material* leftWallMaterial = new LambertianMaterial(blacktex, redtex);
    Material* rightWallMaterial = new LambertianMaterial(blacktex, greentex);
    
    //walls
    scene->add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(550.f, 000.f, 000.f)*scale, nullptr, floorMaterial)); //floor
    scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(-550.f, 000.f, 000.f)*scale, nullptr, grey)); //ceiling
    scene->add(new Quad(Point(000.f, 000.f, 560.f)*scale, Vector(000.f, 550.f, 000.f)*scale, Vector(550.f, 000.f, 000.f)*scale, nullptr, grey)); //back wall
    scene->add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(000.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, nullptr, rightWallMaterial)); //right wall
    scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, -550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, nullptr, leftWallMaterial)); //left wall


    //Animated Objects:
    SimpleGroup* moving = new SimpleGroup();
    moving->add(new Sphere(Point(150.0f, 100.0f, 240.0f)*scale, 99.0f*scale, nullptr, sphereMaterial));
    moving->add(new Sphere(Point(450.0f, 50.0f, 50.0f)*scale, 49.0f*scale, nullptr, yellowmat));
    AnimatedPrimitive* verticalMov = new AnimatedPrimitive(moving,Vector(0,30*scale,0));
    scene->add(verticalMov);


    //tall box
    makeBox(scene, Point(265.f, 000.1f, 296.f)*scale, Vector(049.f, 000.f, 160.f)*scale, Vector(158.f, 000.f, -049.f)*scale, Vector(000.f, 330.f, 000.f)*scale, nullptr, grey);

    //Lights
    ConstantTexture* lightsrctex = new ConstantTexture(RGBColor::rep(35.0f));
    Material* lightsource = new LambertianMaterial(lightsrctex, blacktex);

    Quad* light = new Quad(Point(213*scale,549.99f*scale,227*scale), Vector(130*scale,0,0), Vector(0,0,105*scale), nullptr, lightsource);
    AreaLight als(light);
    world.light.push_back(&als);
    scene->add(light);

    //point light
    world.light.push_back(new PointLight(Point(490*scale,159.99f*scale,279.5f*scale),RGBColor(40000.0f*scale*scale,0,0)));
    world.light.push_back(new PointLight(Point(40*scale,159.99f*scale,249.5f*scale),RGBColor(5000.0f*scale*scale,30000.0f*scale*scale,5000.0f*scale*scale)));
    
    // world.light.push_back(new PointLight(Point((278)*scale,429.99f*scale,(279.5f)*scale),RGBColor::rep(100000.0f*scale*scale)));
    // world.light.push_back(new PointLight(Point(478*scale,229.99f*scale,(-59.5f)*scale),RGBColor::rep(150000.0f*scale*scale)));



    RecursiveRayTracingIntegrator integrator(&world, 6);

    Renderer engine(cam, &integrator);
    if (numSamples>1)
        engine.setSamples(numSamples);
    engine.render(img);
    img.writePNG(filename);

}

}

void a_distributed() {
    PerspectiveCamera* cam = new PerspectiveCamera(Point(0.278f, 0.273f, -0.800f), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);
    DOFPerspectiveCamera* dofcam = new DOFPerspectiveCamera(Point(0.278f, 0.273f, -0.8f), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f, 1.025f, 0.045f);

    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));
    Material* floorMaterial1 = new LambertianMaterial(blacktex, whitetex);
    Material* floorMaterial2 = new FuzzyMirrorMaterial(2.485f, 3.433f, 0.05f);

    Material* sphereMaterial1 = floorMaterial1;
    ImageTexture* fire = new ImageTexture("models/fire.png");
    ConstantTexture* light_color = new ConstantTexture(RGBColor(1, 1, 1));
    Material* sphereMaterial2 = new GlassMaterial(2.0f, light_color);

    CombineMaterial* combined = new CombineMaterial();
    //combined->add(new PhongMaterial(perlinTex, 10.0f), 0.62f);
    combined->add(new PhongMaterial(fire, 3.0f), 0.5f);
    //combined->add(new FlatMaterial(fire), 0.2);
    combined->add(new  GlassMaterial(2.0f, nullptr), 0.8f);
   // renderCornellbox(0.001f, "a6-5.png", cam, sphereMaterial1, floorMaterial1, 30);
    //renderCornellbox(0.001f, "a6-6.png", cam, sphereMaterial2, floorMaterial2, 200);
    renderCornellbox(0.001f, "a6-6.png", cam, combined, floorMaterial2, 200);
    //renderCornellbox(0.001f, "a6-7a.png", dofcam, sphereMaterial2, floorMaterial2, 30);

    
    // auto t_start = std::chrono::steady_clock::now();
    // ///////////////
    //renderCornellbox(0.001f, "a6-7b.png", dofcam, sphereMaterial2, floorMaterial2, 1000);
    // /////////////// yes 1.76478e+06 ms, no 
    // auto t_end = std::chrono::steady_clock::now();

    // double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    // std::cout << "Time taken to render: " << elapsed_time_ms << " ms" << std::endl;
    // std::cout << "Time taken to render: " << elapsed_time_ms/1000 << " secs" << std::endl;
    // std::cout << "Time taken to render: " << elapsed_time_ms/60000 << " min" << std::endl;
    // std::cout << "Time taken to render: " << elapsed_time_ms/3600000 << " hours" << std::endl;
    


    //EXTRA
    //renderMotionBlurr(0.001f, "a6-Extra-MotionBlurr-10.png", cam, sphereMaterial1, floorMaterial1, 10);
    //renderMotionBlurr(0.001f, "a6-Extra-MotionBlurr-30.png", cam, sphereMaterial1, floorMaterial1, 30);
    //renderMotionBlurr(0.001f, "a6-Extra-MotionBlurr-1000.png", cam, sphereMaterial1, floorMaterial1, 1000);

}


