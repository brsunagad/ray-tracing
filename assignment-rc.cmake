cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
)

set(ASSIGNMENT_SOURCES
   ${MY_ADDITIONAL_SOURCES}
    main/a_scene.cpp
)

file(COPY

    models/rc_models/barrels.obj
    models/rc_models/barrels.mtl
    models/rc_models/PirateProps_Barrel_Texture_Color.tga.png
    models/rc_models/PirateProps_Barrel_Texture_Metal.tga.png
    models/rc_models/PirateProps_Barrel_Texture_Roughness.tga.png
    models/rc_models/PirateProps_Barrel_Texture_Normal.tga.png

    models/rc_models/bottles.obj
    models/rc_models/bottles.mtl
    models/rc_models/PirateProps_Bottle_Texture_Color.tga.png
    models/rc_models/PirateProps_Bottle_Texture_Roughness.tga.png
    models/rc_models/PirateProps_Bottle_Texture_Normal.tga.png

    models/rc_models/sheild.obj
    models/rc_models/sheild.mtl
    models/rc_models/lambert1_albedo.png
    models/rc_models/lambert1_metallic.png
    models/rc_models/lambert1_normal.png
    models/rc_models/lambert1_roughness.png

    models/rc_models/horn.obj
    models/rc_models/horn.mtl
    models/rc_models/Horn_low_Horn_Normal.png
    models/rc_models/Horn_low_Horn_BaseColor.png
    models/rc_models/Horn_low_Horn_Roughness.png
    models/rc_models/Horn_low_Horn_Metallic.png


    models/rc_models/axe.obj
    models/rc_models/axe.mtl
    models/rc_models/HACHA_Normal.png
    models/rc_models/HACHA_BaseColor.png
    models/rc_models/HACHA_Roughness.png    
    models/rc_models/HACHA_Metallic.png


    models/rc_models/toothless.obj
    models/rc_models/toothless.mtl
    models/rc_models/toothless_export_model_toothless_sg_Normal.png
    models/rc_models/toothless_export_model_toothless_sg_BaseColor.png
    models/rc_models/toothless_export_model_toothless_sg_Roughness.png

    models/rc_models/lamp.obj
    models/rc_models/lamp.mtl
    models/rc_models/rocksColor.png
    models/rc_models/rocksSpec.png

    models/rc_models/red_dragon.obj
    models/rc_models/red_dragon.mtl
    models/rc_models/dragonNor.png
    models/rc_models/dragonColor2.png
    models/rc_models/dragonSpecInt.png

    models/rc_models/fire.obj
    models/rc_models/fire.mtl
    models/rc_models/fire.png

    models/rc_models/fence.obj
    models/rc_models/fence.mtl
    models/rc_models/Line001_Normal.png
    models/rc_models/Line001_Albedo.png
    models/rc_models/Line001_Specular.png

    models/rc_models/planks.obj
    models/rc_models/planks.mtl
    models/rc_models/planks_normal.png
    models/rc_models/planks_color.png
    DESTINATION ${CMAKE_BINARY_DIR}/models
)
