qt_add_library(model STATIC model.hpp)
target_include_directories(model INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(model PUBLIC Qt::Core Qt::Widgets timer)
