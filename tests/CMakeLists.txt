list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(AddGoogleTest)

add_executable(tests test_coreImpl.cpp)
target_link_libraries(tests PRIVATE gtest_main gmock coreImpl)

include(GoogleTest)
gtest_discover_tests(tests XML_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/tests/reports")

