cmake_minimum_required(VERSION 3.16)
project(SkibidiCalculator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Qt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Option to build the main app
option(BUILD_APP "Build the SkibidiCalculator app" ON)

# === Main app ===
add_executable(SkibidiCalculator
    main.cpp
    calculator.cpp
    calculator.h
    mathlib.cpp
    mathlib.h
)

target_include_directories(SkibidiCalculator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(SkibidiCalculator
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

if(WIN32)
    set_target_properties(SkibidiCalculator PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

install(TARGETS SkibidiCalculator
    RUNTIME DESTINATION bin
)

# === Tests (optional) ===

option(BUILD_TESTS "Build and run unit tests" OFF)

if(BUILD_TESTS)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(test_math
        mathlib.cpp
        mathlib.h
        tdd_test_math_library.cpp
    )

    target_include_directories(test_math PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    target_link_libraries(test_math
        GTest::gtest
        GTest::gtest_main
        pthread
    )

    include(GoogleTest)
    gtest_discover_tests(test_math)
endif()
