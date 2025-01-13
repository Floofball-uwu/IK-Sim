add_library(iklib
        IkNode.cpp
        IkArm.cpp
        IkSolver.cpp
)

add_subdirectory(math)

target_include_directories(iklib PRIVATE "${CMAKE_SOURCE_DIR}/include/ik-lib")
target_link_libraries(iklib iklib-math)