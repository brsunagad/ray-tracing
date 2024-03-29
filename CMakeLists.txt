cmake_minimum_required(VERSION 3.9.4 FATAL_ERROR)

project(CG1-raytracer)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "limited config" FORCE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ASSIGNMENT_LIBRARIES)

find_package(PNG QUIET)
if (PNG_FOUND)
    include_directories(${PNG_INCLUDE_DIRS})
    add_definitions(${PNG_DEFINITIONS})
    set(ASSIGNMENT_LIBRARIES ${ASSIGNMENT_LIBRARIES} ${PNG_LIBRARIES})
elseif(WIN32 AND MSVC)
    add_definitions(-DGDIPLUS_SUPPORT)
    set(ASSIGNMENT_LIBRARIES ${ASSIGNMENT_LIBRARIES} gdiplus)
else()
    find_package(PNG)
    message(FATAL_ERROR "libpng-dev is required to build the CG1-raytracer.\nPlease install libpng-dev.")
endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(ALL_ASSIGNMENT_SOURCES)

file(GLOB ASSIGNMENT_FILES "${CMAKE_CURRENT_SOURCE_DIR}/assignment-*.cmake")
foreach(f ${ASSIGNMENT_FILES})
    get_filename_component(_fname ${f} NAME_WE)
    message(STATUS "Found files of ${_fname}")
    include(${f})
    foreach(_s ${ASSIGNMENT_SOURCES})
        message(STATUS " - ${_s}")
    endforeach()
    list(APPEND ALL_ASSIGNMENT_SOURCES ${ASSIGNMENT_SOURCES})
endforeach()

add_executable(cgray ${ALL_ASSIGNMENT_SOURCES} main/main.cpp "rt/solids/quadric.cpp"   "main/a_scene.cpp")


# OpenMP support
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(cgray OpenMP::OpenMP_CXX)
endif()
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:1800000")

# Compile with IPO in Release mode
include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT IPO_ERROR_MESSAGE)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    if (IPO_SUPPORTED)
        message(STATUS "Compiling with IPO")
        set_property(TARGET cgray PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
        message(STATUS "IPO unavailable on this platform: ${IPO_ERROR_MESSAGE}")
    endif()
endif()
target_link_libraries(cgray ${ASSIGNMENT_LIBRARIES})

include(cgray-tests.cmake OPTIONAL)
include(cgray-bench.cmake OPTIONAL)
