add_library(iklib-math
        Vector3.cpp
        Vector4.cpp
        Matrix4.cpp
)

target_include_directories(iklib-math PRIVATE "${CMAKE_SOURCE_DIR}/include/ik-lib/math")