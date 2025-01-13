#ifndef IKSOLVER_HPP
#define IKSOLVER_HPP

#include "IkArm.hpp"

namespace IkLib {
class IkSolver {
    public:
        explicit IkSolver() = default;

    private:
        IkArm ikArm;
};

}

#endif //IKSOLVER_HPP
