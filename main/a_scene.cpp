
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
#include <rt/lights/arealight.h>
#include <rt/materials/phong.h>
#include <rt/materials/glass.h>
#include <rt/materials/mirror.h>
#include <rt/materials/flatmaterial.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/combine.h>
#include <rt/textures/perlin.h>
#include <rt/cameras/dofperspective.h>
#include <chrono>
#include <rt/coordmappers/coordmapper.h>
#include <core/float4.h>
#include <rt/solids/quad.h>
using namespace rt;
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
MatLib* lamp_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* rock_color = new ImageTexture("models/rocksColor.png");

   // matlib->insert(std::pair<std::string, Material*>("base", new PhongMaterial(new ConstantTexture(RGBColor::rep(0.1f)), 10.0f)));
    //matlib->insert(std::pair<std::string, Material*>("vetro", new GlassMaterial(1.5f, nullptr)));
    matlib->insert(std::pair<std::string, Material*>("rock", new LambertianMaterial(blacktex, rock_color)));
    //matlib->insert(std::pair<std::string, Material*>("rock", new FlatMaterial(rock_color)));

    CombineMaterial* combined = new CombineMaterial();
    combined->add(new PhongMaterial(new ConstantTexture(RGBColor::rep(0.1f)), 10.0f), 0.62f);
    combined->add(new MirrorMaterial(0.0f, 0.0f), 0.38f);

    matlib->insert(std::pair<std::string, Material*>("base", combined));

    CombineMaterial* combined2 = new CombineMaterial();
    ImageTexture* fire = new ImageTexture("models/fire.png");
    //combined2->add(new PhongMaterial(fire, 10.0f), 0.01f);
    combined2->add(new PhongMaterial(new ConstantTexture(RGBColor(0.6, 0.3, 0.2 )/5), 10.0f), 0.003f);

    combined->add(new FlatMaterial(fire), 0.2);
    combined2->add(new  GlassMaterial(1.5f, nullptr), 10.0f);
    combined2->isGlass = true;
    matlib->insert(std::pair<std::string, Material*>("vetro", combined2));
    return matlib;
}

MatLib* fire_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));

    ImageTexture* fire = new ImageTexture("models/fire.png");
    //matlib->insert(std::pair<std::string, Material*>("fire_breath", new FlatMaterial(fire)));

    CombineMaterial* combined = new CombineMaterial();
    //combined->add(new PhongMaterial(perlinTex, 10.0f), 0.62f);
    combined->add(new PhongMaterial(fire, 10.0f), 0.5f);
    //combined->add(new PhongMaterial(new ConstantTexture(RGBColor(1, 0.7, 0.3)), 10.0f), 0.5f);
    combined->add(new PhongMaterial(new ConstantTexture(RGBColor(1.f, 0.0, 0.0)), 5.0f), 0.3f);
    combined->add(new FlatMaterial(new ConstantTexture(RGBColor(0.f, 0.0, 1))), 0.09);
    combined->add(new  GlassMaterial(1.5f, nullptr), 4.0f);
    matlib->insert(std::pair<std::string, Material*>("fire_breath", combined));

    return matlib;
}

MatLib* red_dragon_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));

    ImageTexture* diffuse = new ImageTexture("models/dragonColor2.png");
    //matlib->insert(std::pair<std::string, Material*>("red_dragon", new FlatMaterial(fire)));
    matlib->insert(std::pair<std::string, Material*>("red_dragon", new CookTorranceMaterial(diffuse, blacktex, 0.5f, 0.5f, 1.0f)));
    return matlib;
}


MatLib* barrels_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));

    ImageTexture* diffuse = new ImageTexture("models/PirateProps_Barrel_Texture_Color.tga.png");
    ImageTexture* specular = new ImageTexture("models/PirateProps_Barrel_Texture_Metal.tga.png");
    //matlib->insert(std::pair<std::string, Material*>("Barrel_PropMaterial", new LambertianMaterial(blacktex, diffuse)));
    matlib->insert(std::pair<std::string, Material*>("Barrel_PropMaterial", new CookTorranceMaterial(diffuse, blacktex, 0.5f, 0.5f, 1.0f)));
    return matlib;
}

MatLib* bottles_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));

    ImageTexture* diffuse = new ImageTexture("models/PirateProps_Bottle_Texture_Color.tga.png");
    ImageTexture* specular = new ImageTexture("models/PirateProps_Bottle_Texture_AO.tga.png");
    //matlib->insert(std::pair<std::string, Material*>("bottle", new LambertianMaterial(blacktex, diffuse)));
    //matlib->insert(std::pair<std::string, Material*>("bottle", new CookTorranceMaterial(diffuse, blacktex, 0.5f, 0.5f, 1.0f)));
    matlib->insert(std::pair<std::string, Material*>("bottle", new PhongMaterial(diffuse, 0.8f)));
    return matlib;
}

MatLib* horn_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* diffuse = new ImageTexture("models/Horn_low_Horn_BaseColor.png");

    //matlib->insert(std::pair<std::string, Material*>("horn", new LambertianMaterial(blacktex, diffuse)));
    matlib->insert(std::pair<std::string, Material*>("horn", new CookTorranceMaterial(diffuse, blacktex, 0.5f, 0.5f, 1.0f)));
    return matlib;
}

MatLib* axe_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* diffuse = new ImageTexture("models/HACHA_BaseColor.png");

    //matlib->insert(std::pair<std::string, Material*>("axe", new LambertianMaterial(blacktex, diffuse)));
    matlib->insert(std::pair<std::string, Material*>("axe", new CookTorranceMaterial(diffuse, blacktex, 0.5f, 0.5f, 1.0f)));
    return matlib;
}

MatLib* planks_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* diffuse = new ImageTexture("models/planks_color.png");

    //matlib->insert(std::pair<std::string, Material*>("PlankSurface.001", new LambertianMaterial(blacktex, diffuse)));
    matlib->insert(std::pair<std::string, Material*>("PlankSurface.001", new CookTorranceMaterial(diffuse, blacktex, 0.5f, 0.5f, 1.0f)));

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
    ImageTexture* diffuse = new ImageTexture("models/toothless_export_model_toothless_sg_BaseCo.png");

    //matlib->insert(std::pair<std::string, Material*>("toothless_sg", new LambertianMaterial(blacktex, diffuse)));
    matlib->insert(std::pair<std::string, Material*>("toothless_sg", new CookTorranceMaterial(diffuse, blacktex, 0.5f, 0.5f, 1.0f)));

    return matlib;
}

MatLib* sheild_matlib() {
    MatLib* matlib = new MatLib;
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* diffuse = new ImageTexture("models/lambert1_albedo.png");
    ImageTexture* specular = new ImageTexture("models/lambert1_metallic.png");
    matlib->insert(std::pair<std::string, Material*>("sheild", new CookTorranceMaterial(diffuse, blacktex, 0.5f, 0.5f, 1.0f)));
    //matlib->insert(std::pair<std::string, Material*>("sheild", new LambertianMaterial(blacktex, diffuse)));

    return matlib;
}


void a_scene() {
    //Image img(480, 320);
   //Image img(800, 600);
    // Image img(1080, 720);
     //Image img(1920, 1080);
   Image img(2160, 1440);
     
    BVH* scene = new BVH();
    //SimpleGroup* scene = new SimpleGroup();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    loadOBJ(scene, "models/", "planks.obj", nullptr);
    loadOBJ(scene, "models/", "axe.obj", nullptr);
    loadOBJ(scene, "models/", "fence.obj", new ImageTexture("models/Line001_Normal.png"));
    loadOBJ(scene, "models/", "bottles.obj", nullptr);
    loadOBJ(scene, "models/", "barrels.obj", new ImageTexture("models/PirateProps_Barrel_Texture_Normal.tga.png", ImageTexture::REPEAT, ImageTexture::NEAREST));
    loadOBJ(scene, "models/", "sheild.obj", new ImageTexture("models/lambert1_normal.png", ImageTexture::REPEAT, ImageTexture::NEAREST));
    loadOBJ(scene, "models/", "horn.obj", new ImageTexture("models/Horn_low_Horn_Normal.png", ImageTexture::REPEAT, ImageTexture::NEAREST));
    loadOBJ(scene, "models/", "toothless.obj", new ImageTexture("models/toothless_export_model_toothless_sg_Normal.png", ImageTexture::REPEAT, ImageTexture::NEAREST));
    loadOBJ(scene, "models/", "lamp.obj", nullptr, lamp_matlib());
    loadOBJ(scene, "models/", "fire.obj", nullptr, fire_matlib());
    loadOBJ(scene, "models/", "red_dragon.obj", nullptr);
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 

    
    World world;
 
    int samples = 10, depth = 30;
    //Lighting

    float intensity = 10;
   // RGBColor light_color = RGBColor(1, 0.7, 0.3);
    RGBColor light_color = RGBColor(1, 0.54, 0.173);
    //world.light.push_back(new PointLight(Point(0.416149, 1.27344, 3.46079), RGBColor(1, 1, 1)*intensity));
    world.light.push_back(new PointLight(Point(-12.3755, 6.89785, -20.6596), RGBColor(0.167, 0.521, 1) * intensity*50));//ambient near bottle old
    world.light.push_back(new PointLight(Point(2.6262, 6.89785, -20.6596), RGBColor(0.167, 0.521, 1) * intensity*20));//ambient near shield
    //world.light.push_back(new PointLight(Point(-7.89528 , 3.1092, -12.4029), RGBColor(1, 0.7, 0.3) * intensity * 100));//in lamp
    //world.light.push_back(new PointLight(Point(-8.0487 , 3.10916, -13.1346), RGBColor(1, 0.7, 0.3) * intensity *10));
    //world.light.push_back(new PointLight(Point(-8.66465 , 3.10916 , -12.3375), RGBColor(1, 0.7, 0.3) * intensity *10));
    //world.light.push_back(new PointLight(Point(-7.89472, 3.1092 , -11.5766 ), RGBColor(1, 0.7, 0.3) * intensity *5));
    //world.light.push_back(new PointLight(Point(-7.27575 , 3.1092 , -12.3375 ), RGBColor(1, 0.7, 0.3) * intensity *5));
    // 
    // 
   // world.light.push_back(new PointLight(Point(-7.84322 , 9.96356 , -20.8048 ), RGBColor(0.167, 0.521, 1) * intensity * 10));//ambient night effect
    world.light.push_back(new PointLight(Point(-7.85498, 3.03516, -12.0143), light_color * intensity *15));//top
    world.light.push_back(new PointLight(Point(-8.0378, 2.5053 , -11.8969), light_color * intensity *4));
    world.light.push_back(new PointLight(Point(-7.9733 , 2.5053 , -12.2115), light_color * intensity *4));
    world.light.push_back(new PointLight(Point(-7.66991, 2.5053 , -11.9743), light_color * intensity *4));
    ////////////////////////////////////////////////////////
    ConstantTexture* lightsrctex = new ConstantTexture(RGBColor::rep(35.0f));
    ImageTexture* imgtex = new ImageTexture("models/environmentMap2.png");
    Material* lightsource = new LambertianMaterial(imgtex, new ConstantTexture(RGBColor::rep(0.f)));
    CombineMaterial* combined = new CombineMaterial();
    combined->add(lightsource, 1.50f);
    combined->add(new MirrorMaterial(0.0f, 0.0f), 5.f);
    CoordMapper* mapper = new QuadMapper(Vector::rep(-2.f), Vector::rep(3.0f));
    Quad* light = new Quad(Point(60.7455, -4.52399, 64.5196) , Point(-45.3245 , 41.1383, 46.5963) - Point(60.7455, -4.52399, 64.5196), Point(80.2167 , -4.524 , -50.7106 ) - Point(60.7455, -4.52399, 64.5196), mapper, combined);
    AreaLight als(light, 8);
    world.light.push_back(&als);
    scene->setenv(light);
    ///////////////////////////////////////////////////////
    scene->rebuildIndex();
    world.scene = scene;
   // PerspectiveCamera cam(Point(-23.766264, 2.119421, -14.954997), Point(-22.780579, 2.149030, -14.789021) - Point(-23.766264, 2.119421, -14.954997), Vector(-0.027284, 0.999495, -0.016274), pi / 6.5, pi / 4.5);
    DOFPerspectiveCamera cam(Point(-23.766264, 2.119421, -14.954997), Point(-22.780579, 2.149030, -14.789021) - Point(-23.766264, 2.119421, -14.954997), Vector(-0.027284, 0.999495, -0.016274), pi / 6.5, pi / 4.5, 18.025f, 0.08f);
    RecursiveRayTracingIntegrator integrator(&world, 5);

    auto t_start = std::chrono::high_resolution_clock::now();

    Renderer engine(&cam, &integrator);
    engine.setSamples(samples);
    engine.render(img);

    auto t_end = std::chrono::high_resolution_clock::now();

    img.writePNG("a_scene.png");

    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time taken to render a_scene.png: " << elapsed_time_ms / 1000 / 60<< " mins" << std::endl;

    std::string filename = "a_scene_s" + std::to_string(samples) + "_d" + std::to_string(depth) + ".png";
    //img.writePNG(filename);


    delete scene;


}