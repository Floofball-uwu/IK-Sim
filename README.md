# Inverse Kinematics test rig

A simple simulation using threepp for developing inverse kinematics... from scratch... so it can work on microcontrollers like Arduino without the STL library... *sigh*

# Several libraries??
The core inverse kinematics is based off *Inverse Kinematics Algorithms* by chFleschutz (a godsend), found [here](https://github.com/chFleschutz/inverse-kinematics-algorithms) and internally known as `ik-algorithms`.

Then there's the modified 3D counterpart named `ik-algorithms-3d`. The Standard Library may be utilized here for logic. 

Lastly the goal is to make perhaps a more or less optimized, but fully STL-less version of the 3D one, known as `ik-lib`. This version is then intended to be used on microcontrollers.

## Assumptions within the ik-lib
- No access to the C++ Standard Library, because Arduino... or microcontrollers in general
  - Exceptions: common math functions like trigonometric ones and such.
    - In such cases, a wrapper function will be made for easy replacement with an existing implementation.
- Exception handling? What exception handling?
