add_library(ik-algorithms-3d
        Leg.cpp
        Skeleton3.cpp
        CCD3.cpp
        IKSolver3.cpp
)

target_include_directories(ik-algorithms-3d PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(ik-algorithms-3d PRIVATE "${CMAKE_SOURCE_DIR}/include/ik-algorithms-3d")
target_link_libraries(ik-algorithms-3d PRIVATE threepp ik-algorithms)