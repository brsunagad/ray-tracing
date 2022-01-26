
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/groups/bvh.h>
#include <rt/groups/simplegroup.h>
#include <rt/solids/sphere.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/casting.h>
#include <rt/integrators/recraytrace.h>
#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>
#include <rt/materials/cooktorrance.h>
#include <rt/lights/pointlight.h>
#include <rt/materials/phong.h>
#include <rt/materials/glass.h>
#include <rt/materials/mirror.h>
#include <rt/materials/flatmaterial.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/combine.h>
#include <chrono>

using namespace rt;

MatLib* getHelmetMatlib() {
    MatLib* matlib = new MatLib;
    ImageTexture* tex1 = new ImageTexture("models/DefaultMaterial_albedo.png");
    ImageTexture* tex2 = new ImageTexture("models/DefaultMaterial_roughness.png");
    matlib->insert(std::pair<std::string, Material*>("bar_low", new CookTorranceMaterial(tex1, tex2, 0.8, 0.2, 0.3)));
    matlib->insert(std::pair<std::string, Material*>("basecorne_low", new CookTorranceMaterial(tex1, tex2, 0.8, 0.2, 0.3)));
    matlib->insert(std::pair<std::string, Material*>("casque_low", new CookTorranceMaterial(tex1, tex2, 0.8, 0.2, 0.3)));
    matlib->insert(std::pair<std::string, Material*>("corne_low", new CookTorranceMaterial(tex1, tex2, 0.8, 0.2, 0.3)));

    return matlib;
}

MatLib* lamp_matlib() {
    MatLib* matlib = new MatLib;
    Texture*  blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* rock_color = new ImageTexture("models/rocksColor.png");

    matlib->insert(std::pair<std::string, Material*>("base", new PhongMaterial(new ConstantTexture(RGBColor::rep(0.035f)), 10.0f)));
    matlib->insert(std::pair<std::string, Material*>("vetro", new GlassMaterial(1.33f)));
    matlib->insert(std::pair<std::string, Material*>("rock", new LambertianMaterial(blacktex,rock_color)));

    ImageTexture* fire = new ImageTexture("models/fire.png");
    matlib->insert(std::pair<std::string, Material*>("fire_breath", new FlatMaterial(fire)));

    ImageTexture* dragon = new ImageTexture("models/dragonColor2.png");
    //matlib->insert(std::pair<std::string, Material*>("red_dragon", new LambertianMaterial(blacktex, dragon)));
    matlib->insert(std::pair<std::string, Material*>("red_dragon", new FlatMaterial(dragon)));
    return matlib;
}


void a_scene() {
    Image img(800, 600);
    //Image img(2160, 1440);
    //Image img(1080, 720);

    BVH* scene = new BVH();


    // MatLib* matlib_helmet = getHelmetMatlib();
    //loadOBJ(scene, "models/", "helmet.obj");
    /*loadOBJ(scene, "models/", "lamp.obj", lamp_matlib());
    loadOBJ(scene, "models/", "tree_trunk.obj");
    loadOBJ(scene, "models/", "toothless.obj");
    loadOBJ(scene, "models/", "red_dragon.obj");
    loadOBJ(scene, "models/", "fire_breath.obj", fire_breath_matlib());*/

    loadOBJ(scene, "models/", "planes.obj");
    loadOBJ(scene, "models/", "barrels.obj");
    loadOBJ(scene, "models/", "sheild.obj");
    loadOBJ(scene, "models/", "horn.obj");
    loadOBJ(scene, "models/", "axe.obj");
    loadOBJ(scene, "models/", "toothless.obj");
    loadOBJ(scene, "models/", "lamp.obj", lamp_matlib());
    scene->rebuildIndex();
    World world;
    world.scene = scene;

    //Lighting

    float intensity = 10000;
    //world.light.push_back(new PointLight(Point(0.416149, 1.27344, 3.46079), RGBColor(1, 1, 1)*intensity));
    world.light.push_back(new PointLight(Point(-14.7925, 13.9556, -14.1935), RGBColor(1, 1, 1) * intensity));

    // PerspectiveCamera cam(Point(0.367128, 0.344247, 6.795460), Point(0.255833, 0.400069, 5.803241) - Point(0.367128, 0.344247, 6.795460), Vector(0.006222, 0.998441, 0.055474), pi / 8, pi / 6);
    PerspectiveCamera cam(Point(-24.137545, 1.560391, -11.216356), Point(-23.139908, 1.623184, -11.188487) - Point(-24.137545, 1.560391, -11.216356), Vector(-0.062769, 0.998027, -0.001754), pi / 8, pi / 6);
    RecursiveRayTracingIntegrator integrator(&world);

    auto t_start = std::chrono::high_resolution_clock::now();
    
    Renderer engine(&cam, &integrator);
    //engine.setSamples(10);
    engine.render(img);
    
    auto t_end = std::chrono::high_resolution_clock::now();

    img.writePNG("a_scene.png");

    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time taken to render a_scene.png: " << elapsed_time_ms/1000 << " s" << std::endl;
    
    delete scene;


}