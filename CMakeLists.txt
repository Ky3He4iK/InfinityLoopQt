cmake_minimum_required(VERSION 3.14)
project(game)

set(CMAKE_AUTOMOC ON)


set(CMAKE_CXX_STANDARD 17)

add_executable(game main.cpp Field.cpp Field.h gui/FieldLayout.cpp gui/FieldLayout.h gui/FieldCellWidget.cpp gui/FieldCellWidget.h gui/FieldCellData.cpp gui/FieldCellData.h gui/util/GridLayoutUtil.cpp gui/util/GridLayoutUtil.h gui/ControlsWidget.cpp gui/ControlsWidget.h)

include_directories(usr/local/include)
link_directories(usr/local/lib)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
