cmake_minimum_required(VERSION 3.16)
project(MathLibraryTests VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt compatibility (optional):
# find_package(Qt6 REQUIRED COMPONENTS Core)
# set(QT_LIBS Qt6::Core)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test executable
add_executable(test_math
    mathlib.cpp
    tdd_test_math_library.cpp
)

# Include local headers
target_include_directories(test_math PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link with GoogleTest and pthread
target_link_libraries(test_math
    GTest::gtest
    GTest::gtest_main
    pthread
    # ${QT_LIBS}  # Uncomment if using Qt
)

include(GoogleTest)
gtest_discover_tests(test_math)