#ifndef IKTREE_HPP
#define IKTREE_HPP

#include "IkNode.hpp"

class IkTree {
    public:
        IkTree();

        IkNode getNode(int i);
    private:
        IkNode nodes[];
};

#endif //IKTREE_HPP
