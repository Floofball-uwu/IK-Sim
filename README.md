# Inverse Kinematics test rig

A simple simulation using threepp for developing inverse kinematics... from scratch... so it can work on microcontrollers like Arduino without the STL library... *sigh*

# Several libraries??
The core inverse kinematics is based off *Inverse Kinematics Algorithms* by chFleschutz (a godsend), found [here](https://github.com/chFleschutz/inverse-kinematics-algorithms) and internally known as `ik-algorithms`.

Then there's the modified 3D counterpart named `ik-algorithms-3d`. The Standard Library may be utilized here for logic. 

Lastly the goal is to make perhaps a more or less optimized, but fully STL-less version of the 3D one, known as `ik-lib`. This version is then intended to be used on microcontrollers.

# TODO
- Start with own implementation
- Make 3D using multiple 2D planar solvers, one for each axis.
- Perhaps somehow smartify the IK solver regarding picking angles and such. (Preferred angles)
