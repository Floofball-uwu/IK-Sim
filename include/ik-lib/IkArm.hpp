#ifndef IKARM_HPP
#define IKARM_HPP

#include "IkNode.hpp"

namespace IkLib {
class IkArm {
    public:
        explicit IkArm(int joints);

        [[nodiscard]] float getFullLength() const;
        //Simply distance of end affector to (0, 0, 0)
        //The length from E to R:
        //(its root) position + (dir * length)
        //			  E
        //			 /
        //		    /
        //     ----J
        //R----
        [[nodisacrd]] float distanceFromRoot() const;

        int size() const {
            return _size;
        }

        IkNode& operator[](int i) {
            return _nodes[i];
        }

        const IkNode& operator[](int i) const {
            return _nodes[i];
        }

    private:
        int _size;
        IkNode _nodes[];
};

}
#endif //IKARM_HPP
