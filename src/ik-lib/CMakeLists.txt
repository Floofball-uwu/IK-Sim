add_library(iklib
        IkNode.cpp
        IkTree.cpp
        IkSolver.cpp
)

add_subdirectory(math)

target_link_libraries(iklib iklib-math)