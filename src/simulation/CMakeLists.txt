add_library(simulation
        Crane.cpp
        Simulation.cpp
        Tracer.cpp
)

target_include_directories(simulation PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(simulation PRIVATE "${CMAKE_SOURCE_DIR}/include/simulation")
target_link_libraries(simulation PRIVATE threepp::threepp imgui::imgui ik-algorithms)