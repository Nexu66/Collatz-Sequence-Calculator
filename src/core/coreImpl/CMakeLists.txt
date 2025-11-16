qt_add_library(coreImpl STATIC coreImpl.cpp coreImpl.hpp)
target_include_directories(coreImpl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(coreImpl
    PUBLIC
        Qt::Core
        timer
)

