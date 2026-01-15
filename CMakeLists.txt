cmake_minimum_required(VERSION 3.16)

project(3d_viewer LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
add_subdirectory(party/QtGifImage)

set(PROJECT_SOURCES
        controller/controller.cc
        controller/controller.h
        model/parser.cc
        model/parser.h
        view/main.cc
        view/mainwindow.h
        view/custom_opengl_widget.h
        view/custom_opengl_widget.cc
        common/edge.cc
        common/edge.h
        common/types.h
        common/vertex.cc
        common/vertex.h
        model/facade.cc
        model/facade.h
        model/transform.cc
        model/transform.h
        view/SaveImageWidget.h
        view/SaveImageWidget.cc
)

qt_add_resources(SHADER_RESOURCES resources.qrc)

add_executable(3d_viewer
    ${PROJECT_SOURCES}
    view/shaders/line_fragment_shader.fsh
    view/shaders/line_vertex_shader.vsh
    view/mainwindow.cc
    common/IVIew.h
    view/controlW.h
    view/controlW.cc
    view/projection.h
    view/projection.cc
    view/settingswidget.h 
    view/settingswidget.cc
    view/colorpickerlabel.h view/colorpickerlabel.cc
    view/shaders/line_geometry_shader.gsh
    view/shaders/point_fragment_shader.fsh
    view/shaders/point_vertex_shader.vsh
    resources.qrc
    model/model.h

    model/model.cc
    common/IController.h



)
target_include_directories(3d_viewer PRIVATE
    ${CMAKE_SOURCE_DIR}/model/
    ${CMAKE_SOURCE_DIR}/controller/
    ${CMAKE_SOURCE_DIR}/view/
    ${CMAKE_SOURCE_DIR}/common/
    ${CMAKE_SOURCE_DIR}/party/QtGifImage/include/gifimage
)
target_link_libraries(3d_viewer
    PRIVATE
    QtGifImage
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt6::OpenGLWidgets
    ${SHADER_RESOURCES}
)

include(GNUInstallDirs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/party/QtGifImage/include/gifimage)

install(TARGETS 3d_viewer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
