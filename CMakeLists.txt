cmake_minimum_required(VERSION 3.25.1)
project(engine)

# Check command line flags (-DMODE flag)
if (NOT DEFINED mode)
    # Get build directory, check if it the last folder is named debug or release
    get_filename_component(FOLDER_NAME "${CMAKE_BINARY_DIR}" NAME)

    if (FOLDER_NAME STREQUAL "release")
        set(CMAKE_BUILD_TYPE Release)
    else()
        set(CMAKE_BUILD_TYPE Debug)
    endif()

elseif(mode STREQUAL "debug")
    set(CMAKE_BUILD_TYPE Debug)
elseif(mode STREQUAL "release")
    set(CMAKE_BUILD_TYPE Release)
endif()

message("-- Build mode: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_MODE") # Debug mode macro

file(GLOB_RECURSE srcFiles CONFIGURE_DEPENDS src/*.cpp) # All source files
add_library(${PROJECT_NAME} STATIC ${srcFiles}) # Library
target_include_directories(${PROJECT_NAME} PUBLIC include) # Includes

if (NOT EMSCRIPTEN)

    set(CMAKE_CXX_COMPILER g++)

    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)

endif()