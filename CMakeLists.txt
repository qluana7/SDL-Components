cmake_minimum_required(VERSION 3.23)

project(SDL_components
    VERSION 1.0.0
    DESCRIPTION "Components for SDL"
    LANGUAGES CXX
)

# Build Option
set(DEBUG_FILE_OPTION FALSE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_lib/sdl2)

add_compile_options(-Wall -std=c++17)

include_directories(./includes)

file(GLOB_RECURSE SRCS "./src/**.cpp")

if (NOT DEBUG_FILE_OPTION)
    list(FILTER SRCS EXCLUDE REGEX ".*main.cpp")
endif()

if (DEBUG_FILE_OPTION)
    add_executable(SDL_components ${SRCS})
    add_executable(DEBUG ${SRCS})
endif()
add_library(components ${SRCS})

if (DEBUG_FILE_OPTION)
    target_compile_options(DEBUG PUBLIC -g -DDEBUG)
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_gfx REQUIRED)
include_directories(${SDL2_GFX_INCLUDE_DIRS})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

if (DEBUG_FILE_OPTION)
    target_link_libraries(SDL_components ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES} ${SDL2_TTF_LIBRARIES})
    target_link_libraries(DEBUG ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES} ${SDL2_TTF_LIBRARIES})
endif()
target_link_libraries(components PUBLIC ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES} ${SDL2_TTF_LIBRARIES})

add_subdirectory(./examples)