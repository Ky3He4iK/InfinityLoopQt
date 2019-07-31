cmake_minimum_required(VERSION 3.14)
project(game)

set(CMAKE_AUTOMOC ON)


set(CMAKE_CXX_STANDARD 17)

add_executable(game main.cpp Field.cpp Field.h gui/FieldWidget.cpp gui/FieldWidget.h gui/FieldCellWidget.cpp gui/FieldCellWidget.h gui/FieldCellData.cpp gui/FieldCellData.h gui/ControlsWidget.cpp gui/ControlsWidget.h gui/MainWindow.cpp gui/MainWindow.h gui/util/IconManager.cpp gui/util/IconManager.h)

include_directories(usr/local/include)
link_directories(usr/local/lib)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
