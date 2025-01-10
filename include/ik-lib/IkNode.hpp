#ifndef IKNODE_HPP
#define IKNODE_HPP

#include "Constants.hpp"

namespace IkLib {
    class IkNode {
    public:
        IkNode();

        IkLib::Axis rotationAxis = IkLib::Axis::X;

        float getRotation();
        float getLength();

        void setRotation(float rads);
        void setLength(float length);

    private:
        // Rotation in radians
        float rotation = 0.0f;
        float length = 1.0f;
    };

}

#endif //IKNODE_HPP
