# Inverse Kinematics test rig

A simple simulation using threepp for developing inverse kinematics... from scratch... so it can work on microcontrollers like Arduino without the STL library... *sigh*

## Assumptions within the lib
- No access to the C++ Standard Library, because Arduino...
  - Exceptions: common math functions like trigonometric ones and such.
    - In such cases, a wrapper function will be made for easy replacement with an existing implementation. 
- Children are never added or removed within a tree (C arrays are used), so odd behavior can be expected if this is done.
- Exception handling? What exception handling?

## TODO
- math setup
- namespaces (IkLib)
