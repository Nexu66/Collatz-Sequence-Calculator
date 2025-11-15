qt_add_library(controller STATIC controller.cpp controller.hpp)
target_include_directories(controller INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(controller PUBLIC dialog core)
