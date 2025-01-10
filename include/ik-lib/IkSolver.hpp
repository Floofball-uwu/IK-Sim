#ifndef IKSOLVER_HPP
#define IKSOLVER_HPP

#include "IkTree.hpp"

namespace IkLib {
class IkSolver {
    public:
        explicit IkSolver() = default;

    private:
        IkTree ikTree;
};

}

#endif //IKSOLVER_HPP
