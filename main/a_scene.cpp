
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

MatLib* lamp_matlib() {
    MatLib* matlib = new MatLib;
    Texture*  blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* rock_color = new ImageTexture("models/rocksColor.png");

    matlib->insert(std::pair<std::string, Material*>("base", new PhongMaterial(new ConstantTexture(RGBColor::rep(0.035f)), 10.0f)));
    matlib->insert(std::pair<std::string, Material*>("vetro", new GlassMaterial(1.33f)));
    matlib->insert(std::pair<std::string, Material*>("rock", new LambertianMaterial(blacktex,rock_color)));

    return matlib;
}

MatLib* fire_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));

    ImageTexture* fire = new ImageTexture("models/fire.png");
    matlib->insert(std::pair<std::string, Material*>("fire_breath", new FlatMaterial(fire)));

    return matlib;
}

MatLib* red_dragon_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));

    ImageTexture* fire = new ImageTexture("models/dragonColor2.png");
    matlib->insert(std::pair<std::string, Material*>("red_dragon", new FlatMaterial(fire)));

    return matlib;
}


MatLib* barrels_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));

    ImageTexture* barrel = new ImageTexture("models/PirateProps_Barrel_Texture_Color.tga.png");
    matlib->insert(std::pair<std::string, Material*>("Barrel_PropMaterial", new LambertianMaterial(blacktex, barrel)));

    return matlib;
}

MatLib* bottles_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
 
    ImageTexture* bottle = new ImageTexture("models/PirateProps_Bottle_Texture_Color.tga.png");
    matlib->insert(std::pair<std::string, Material*>("bottle", new LambertianMaterial(blacktex, bottle)));
  
    return matlib;
}

MatLib* horn_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* horn = new ImageTexture("models/Horn_low_Horn_BaseColor.png");

    matlib->insert(std::pair<std::string, Material*>("horn", new LambertianMaterial(blacktex, horn)));

    return matlib;
}

MatLib* axe_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* axe = new ImageTexture("models/HACHA_BaseColor.png");

    matlib->insert(std::pair<std::string, Material*>("axe", new LambertianMaterial(blacktex, axe)));

    return matlib;
}

MatLib* planks_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* planks = new ImageTexture("models/planks.png");

    matlib->insert(std::pair<std::string, Material*>("PlankSurface.001", new LambertianMaterial(blacktex, planks)));

    return matlib;
}

MatLib* fence_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* fence = new ImageTexture("models/Line001_Albedo.png");

    matlib->insert(std::pair<std::string, Material*>("fence", new LambertianMaterial(blacktex, fence)));

    return matlib;
}

MatLib* toothless_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* tex = new ImageTexture("models/toothless_export_model_toothless_sg_BaseCo.png");

    matlib->insert(std::pair<std::string, Material*>("toothless_sg", new LambertianMaterial(blacktex, tex)));

    return matlib;
}

MatLib* sheild_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* tex = new ImageTexture("models/lambert1_albedo.png");

    matlib->insert(std::pair<std::string, Material*>("sheild", new LambertianMaterial(blacktex, tex)));

    return matlib;
}


void a_scene() {
    // Image img(800, 600);
    Image img(2160, 1440);
    //Image img(1080, 720);

    BVH* scene = new BVH();
    //SimpleGroup* scene = new SimpleGroup();

    // MatLib* matlib_helmet = getHelmetMatlib();
    //loadOBJ(scene, "models/", "helmet.obj");
    /*loadOBJ(scene, "models/", "lamp.obj", lamp_matlib());
    loadOBJ(scene, "models/", "tree_trunk.obj");
    loadOBJ(scene, "models/", "toothless.obj");
    loadOBJ(scene, "models/", "red_dragon.obj");
    loadOBJ(scene, "models/", "fire_breath.obj", fire_breath_matlib());*/
    //loadOBJ(scene, "models/", "planes.obj", plane_matlib());
    

    loadOBJ(scene, "models/", "planks.obj", planks_matlib());
    loadOBJ(scene, "models/", "fence.obj", fence_matlib());
    loadOBJ(scene, "models/", "bottles.obj", bottles_matlib());
    loadOBJ(scene, "models/", "barrels.obj", barrels_matlib());
    loadOBJ(scene, "models/", "sheild.obj", sheild_matlib());
    loadOBJ(scene, "models/", "horn.obj", horn_matlib());
    loadOBJ(scene, "models/", "axe.obj", axe_matlib());
    loadOBJ(scene, "models/", "toothless.obj", toothless_matlib());
    loadOBJ(scene, "models/", "lamp.obj", lamp_matlib());
    loadOBJ(scene, "models/", "fire.obj", fire_matlib());
    loadOBJ(scene, "models/", "red_dragon.obj", red_dragon_matlib());

    try{
        scene->rebuildIndex();
    } catch (const std::exception& e) // reference to the base of a polymorphic object
    {
        std::cout << e.what(); // information from length_error printed
    }
    
    World world;
    world.scene = scene;

    //Lighting

    float intensity = 1000;
    //world.light.push_back(new PointLight(Point(0.416149, 1.27344, 3.46079), RGBColor(1, 1, 1)*intensity));
    world.light.push_back(new PointLight(Point(-12.3755, 3.89785, -20.6596), RGBColor(1, 1, 1) * intensity));

    // PerspectiveCamera cam(Point(0.367128, 0.344247, 6.795460), Point(0.255833, 0.400069, 5.803241) - Point(0.367128, 0.344247, 6.795460), Vector(0.006222, 0.998441, 0.055474), pi / 8, pi / 6);
    PerspectiveCamera cam(Point(-23.766264, 2.119421, -14.954997), Point(-22.780579, 2.149030, -14.789021) - Point(-23.766264, 2.119421, -14.954997), Vector(-0.027284, 0.999495, -0.016274), pi / 8, pi / 6);
    RecursiveRayTracingIntegrator integrator(&world);

    auto t_start = std::chrono::high_resolution_clock::now();
    
    Renderer engine(&cam, &integrator);
    engine.setSamples(10);
    try{
        engine.render(img);
    } catch (const std::exception& e) // reference to the base of a polymorphic object
    {
        std::cout << e.what(); // information from length_error printed
    }
    
    
    auto t_end = std::chrono::high_resolution_clock::now();

    img.writePNG("a_scene.png");

    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time taken to render a_scene.png: " << elapsed_time_ms/1000 << " s" << std::endl;
    
    delete scene;


}