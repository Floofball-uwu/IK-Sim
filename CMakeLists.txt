cmake_minimum_required(VERSION 3.19)
project(threepp_imgui_demo)

set(CMAKE_CXX_STANDARD 20)

option(SIM_BUILD_TESTS "Build Tests" ON)

include(FetchContent)

set(THREEPP_BUILD_TESTS OFF)
set(THREEPP_BUILD_EXAMPLES OFF)
FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG 2e2397e0b7f0e639f254ea3046b70e53a71f0387
)
FetchContent_MakeAvailable(threepp)

if(SIM_BUILD_TESTS)
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v3.7.1
    )
    FetchContent_MakeAvailable(Catch2)
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(external)
add_subdirectory(src)

add_executable(IK-Sim main.cpp)
target_link_libraries(IK-Sim PRIVATE iklib ik-algorithms simulation threepp imgui)