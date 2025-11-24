cmake_minimum_required(VERSION 3.20)
project(HillelFinal LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

enable_testing()

add_subdirectory(src/app)
add_subdirectory(src/dialog)
add_subdirectory(src/dialog/view)
add_subdirectory(src/core)
add_subdirectory(src/core/model)
add_subdirectory(src/controller)
add_subdirectory(src/timer)
add_subdirectory(tests EXCLUDE_FROM_ALL)
