#ifndef IKNODE_HPP
#define IKNODE_HPP

#include "Constants.hpp"

namespace IkLib {
    class IkNode {
    public:
        IkNode();

        Axis rotationAxis = X;

        float getRotation() const;
        float getLength() const;

        void setRotation(float rads);
        void setLength(float length);

    private:
        // Rotation in radians
        float rotation = 0.0f;
        float length = 1.0f;
    };

}

#endif //IKNODE_HPP
