include(FetchContent)
FetchContent_Declare(
  googletest
  SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/googletest"
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723
  EXCLUDE_FROM_ALL
  FIND_PACKAGE_ARGS NAMES googletest GTest GoogleTest
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
