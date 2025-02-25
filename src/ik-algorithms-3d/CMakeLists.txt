add_library(ik-algorithms-3d
        CCD3.cpp
        IKSolver3.cpp
)

target_link_libraries(ik-algorithms-3d PRIVATE threepp ik-algorithms)
target_include_directories(ik-algorithms-3d PRIVATE "${CMAKE_SOURCE_DIR}/include/ik-algorithms-3d")