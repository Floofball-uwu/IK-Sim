#include "Tracer.hpp"

#include <threepp/materials/LineBasicMaterial.hpp>

#include "threepp/materials/MeshBasicMaterial.hpp"
#include "threepp/objects/Line.hpp"

Tracer::Tracer() {
    auto geometry = threepp::BufferGeometry::create();
    auto material = threepp::LineBasicMaterial::create();
    material->color = threepp::Color(1.0f, 0.4f, 0.4f);
    material->linewidth = 10.0f;

    _pathMesh = threepp::Line::create(geometry, material);
}

const std::shared_ptr<threepp::Line> Tracer::getPathMesh() {
    return _pathMesh;
}

void Tracer::setVisibility(const bool visible) {
    _pathMesh->visible = visible;
}

//BUG: Flickering caused by threepp's triangulation! Because apparently it is a SHADER for a MESH and not a goddamn actual line!!!!!!!!
void Tracer::addPoint(const threepp::Vector3& p) {
    bool redraw = false;

    if(!_pathPoints.empty()) {
        if(_pathPoints.size() >= maxPoints) {
            _pathPoints.erase(_pathPoints.begin());
            redraw = true;
        }

        if(std::abs(_pathPoints.back().lengthSq() - p.lengthSq()) >= distanceBetweenPoints*distanceBetweenPoints) {
            _pathPoints.push_back(p);
            redraw = true;
        }

        if(redraw) {
            _pathMesh->geometry()->setFromPoints(_pathPoints);
        }
        
    } else if(_pathPoints.empty()) {
        _pathPoints.push_back(p);
    }
}
