cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
)

set(ASSIGNMENT_SOURCES
   ${MY_ADDITIONAL_SOURCES}
    main/a_scene.cpp
)

file(COPY
    models/newScene.obj
    models/newScene.mtl
    models/helmet.obj
    models/helmet.mtl
    models/DefaultMaterial_albedo.png
    models/DefaultMaterial_AO.png
    models/DefaultMaterial_metallic.png
    models/DefaultMaterial_roughness.png

    models/rc_models/lamp.obj
    models/rc_models/lamp.mtl
    models/rc_models/rocksColor.png
    models/rc_models/rocksSpec.png

    models/rc_models/tree_trunk.obj
    models/rc_models/tree_trunk.mtl
    models/rc_models/cedar_tree_trunk.jpg

    models/rc_models/toothless.obj
    models/rc_models/toothless.mtl
    models/rc_models/toothless_eye_diffuse.png
    models/rc_models/toothless_body_diffuse.png

    models/rc_models/orange_dragon.obj
    models/rc_models/orange_dragon.mtl
    models/rc_models/OrangeDragon.png

    models/rc_models/red_dragon.obj
    models/rc_models/red_dragon.mtl
    models/rc_models/dragonColor.png
    models/rc_models/dragonSpecInt.png

    models/rc_models/fire_breath.obj
    models/rc_models/fire_breath.mtl
    models/rc_models/fire.jpg

    models/rc_models/purple_dragon.obj
    models/rc_models/purple_dragon.mtl
    models/rc_models/dragon_normal_4k.jpg
    models/rc_models/dragon_diffuse_4k.jpg
    DESTINATION ${CMAKE_BINARY_DIR}/models
)
