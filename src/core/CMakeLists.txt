qt_add_library(core STATIC core.cpp core.hpp)
target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(coreImpl)

target_link_libraries(core PUBLIC coreImpl model)
