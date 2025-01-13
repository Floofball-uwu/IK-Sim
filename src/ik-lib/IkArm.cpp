#include "IkArm.hpp"

namespace IkLib {
    IkArm::IkArm(int joints) {
        _size = joints;
        _nodes[joints] = {};
    }

    float IkArm::getFullLength() const {
        float result = 0;
        for(int i = 0; i < _size; i++) {
            result += _nodes[i].getLength();
        }
        return result;
    }
}
