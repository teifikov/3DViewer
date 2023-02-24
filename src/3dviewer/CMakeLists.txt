cmake_minimum_required(VERSION 3.5)

project(3dviewer VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS OpenGLWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
		glwidget.cpp
		glwidget.h
       ../main.h
       ../Back/parser.c
       ../Back/affine.c
       ../Back/Sound/cow.wav
       ../Back/Sound/x_files.wav

       ../../datasets/giflib/dgif_lib.c
       ../../datasets/giflib/egif_lib.c
       ../../datasets/giflib/gif_err.c
       ../../datasets/giflib/gif_font.c
       ../../datasets/giflib/gif_hash.c
       ../../datasets/giflib/gifalloc.c
       ../../datasets/giflib/quantize.c

       ../../datasets/giflib/gif_lib_private.h
       ../../datasets/giflib/gif_lib.h
       ../../datasets/giflib/gif_hash.h

       ../../datasets/gifimage/qgifglobal.h
       ../../datasets/gifimage/qgifimage_p.h
       ../../datasets/gifimage/qgifimage.cpp
       ../../datasets/gifimage/qgifimage.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3dviewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3dviewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3dviewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3dviewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(3dviewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3dviewer PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_link_libraries(3dviewer PRIVATE Qt${QT_VERSION_MAJOR}::Gui)

set_target_properties(3dviewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3dviewer)
endif()
