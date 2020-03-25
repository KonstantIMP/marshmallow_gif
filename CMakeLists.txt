#Минимальная версия CMAKE
cmake_minimum_required(VERSION 2.6)

project(marshmallow_gif)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

find_package(ImageMagick COMPONENTS Magick++ MagickCore)

include_directories(${ImageMagick_INCLUDE_DIRS})

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCE_EXE  src/main.cpp
                src/gtk_app.cpp
                src/gtk_start_setup.cpp
                src/gtk_setting.cpp
                src/init.cpp
                src/config.cpp
                src/gtk_gif.cpp
                src/qt_start_setup.cpp
                src/qt_mainwindow.cpp
                include/qt_start_setup.hpp
                include/qt_mainwindow.hpp
                include/config.hpp
                include/gtk_app.hpp
                include/gtk_gif.hpp
                include/gtk_setting.hpp
                include/gtk_start_setup.hpp
                include/init.hpp
                lib/queue.hpp
                lib/stack.hpp
                lib/list.hpp
                form/qt_start_setup.ui
                form/qt_mainwindow.ui)

#set(SOURCE_LIB  )

#add_library(app STATIC ${SOURCE_LIB})

add_executable(marshmallow_gif ${SOURCE_EXE})

target_link_libraries(marshmallow_gif ${GTK3_LIBRARIES} ${X11_LIBRARIES} ${ImageMagick_LIBRARIES} Qt5::Widgets)
