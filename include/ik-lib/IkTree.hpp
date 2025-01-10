#ifndef IKTREE_HPP
#define IKTREE_HPP

#include "IkNode.hpp"

namespace IkLib {
class IkTree {
    public:
        explicit IkTree() = default;

    private:
        IkNode nodes[];
};

}
#endif //IKTREE_HPP
