
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
#include <chrono>

using namespace rt;

void a_indexing() {
    Image img(800, 600);

    // Original test
    BVH* scene = new BVH();
    scene->add(new Sphere(Point(2.5f,  .5f,  -1), 0.5  , nullptr, nullptr));
    scene->add(new Sphere(Point(2.5f,  -1.f,  -1), 0.5, nullptr, nullptr));
    scene->add(new Sphere(Point(4.5f,  .5f,  -1), 0.5 , nullptr, nullptr));

    loadOBJ(scene, "models/", "cow.obj", nullptr);
  
    scene->rebuildIndex();
    World world;
    world.scene = scene;

    PerspectiveCamera cam1(Point(-8.85f, -7.85f, 7.0f), Vector(1.0f,1.0f,-0.6f), Vector(0, 0, 1), pi/8, pi/6);
    PerspectiveCamera cam2(Point(16.065f, -12.506f, 1.771f), Point(-0.286f, -0.107f, 1.35f)-Point(16.065f, -12.506f, 1.771f), Vector(0, 0, 1), pi/8, pi/6);
    RayCastingIntegrator integrator(&world);

    Renderer engine1(&cam1, &integrator);
    engine1.render(img);
    img.writePNG("a3-1.png");

    Renderer engine2(&cam2, &integrator);
    engine2.render(img);
    img.writePNG("a3-2.png");


    // Rendering speed test
    // right now we are using a counter to switch between SAH and splitInMiddle heuristic, this is just for comparision and will be deleted later
    BVH* sceneTest1 = new BVH();

    loadOBJ(sceneTest1, "models/", "dragon.obj", nullptr);

     PerspectiveCamera cam3(Point(-2.0f, 0.05f, -0.0f), Point(0.0f, 0.0f, 0.0f) - Point(-2.0f, 0.05f, -0.0f), Vector(0, 1, 0), pi/8, pi/6);//this is for dragon.obj, do not change
    

    // Not using SAH
	 sceneTest1->rebuildIndex();
     world.scene = sceneTest1;
     RayCastingIntegrator integratorTest1(&world);

    auto t_start = std::chrono::high_resolution_clock::now();
    ///////////////
    Renderer engine3(&cam3, &integratorTest1);
    engine3.render(img);
    ///////////////
    auto t_end = std::chrono::high_resolution_clock::now();

    img.writePNG("a3-dragon-noSAH.png");

    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time taken to render a3-dragon-noSAH.png: " << elapsed_time_ms << " ms" << std::endl;


    // Using SAH
   
    sceneTest1->rebuildIndex();
    world.scene = sceneTest1;
    RayCastingIntegrator integratorTest2(&world);
    t_start = std::chrono::high_resolution_clock::now();
 //    ///////////////
     Renderer engine4(&cam3, &integratorTest2);
    engine4.render(img);
    ///////////////
    t_end = std::chrono::high_resolution_clock::now();

    img.writePNG("a3-dragon-SAH.png");

    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time taken to render a3-dragon-SAH.png: " << elapsed_time_ms << " ms" << std::endl;
}