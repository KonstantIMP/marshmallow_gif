#Минимальная версия CMAKE
cmake_minimum_required(VERSION 2.6)

project(marshmallow_gif)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

find_package(ImageMagick COMPONENTS Magick++ MagickCore)

include_directories(${ImageMagick_INCLUDE_DIRS})

set(SOURCE_EXE  src/main.cpp
                src/app.cpp
                src/start_setup.cpp)

set(SOURCE_LIB  src/config.cpp
                src/gif.cpp)

add_library(app STATIC ${SOURCE_LIB})

add_executable(marshmallow_gif ${SOURCE_EXE})

target_link_libraries(marshmallow_gif app ${GTK3_LIBRARIES} ${X11_LIBRARIES} ${ImageMagick_LIBRARIES})
