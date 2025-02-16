#ifndef TRACER_HPP
#define TRACER_HPP

#include <vector>
#include "threepp/math/Vector3.hpp"
#include "threepp/objects/Line.hpp"
#include "threepp/objects/LineSegments.hpp"
#include "threepp/objects/Mesh.hpp"

class Tracer {
public:
    unsigned int maxPoints = 512;
    float distanceBetweenPoints = 1.0f;
    Tracer();

    const std::shared_ptr<threepp::Line> getPathMesh();
    void setVisibility(const bool visible);
    void addPoint(const threepp::Vector3& p);
private:
    std::shared_ptr<threepp::Line> _pathMesh;
    std::vector<threepp::Vector3> _pathPoints;
};

#endif //TRACER_HPP
