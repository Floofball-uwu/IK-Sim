#ifndef CRANE_HPP
#define CRANE_HPP

#include "Utils.hpp"
#include "threepp/objects/Mesh.hpp"

///Visualization class for simulating an arm
///TODO: Make it exist in the world (visual meshes)
///TODO: Make every joint available for input through logic (IKSolver does math -> passes data to Crane -> Crane moves)
class Crane : threepp::Object3D{
public:
  Crane(std::vector<std::shared_ptr<threepp::Mesh>> bones);

  //Sets rotation of each joint appropriately, one by one, around the determined axis
  void parseIkData(std::vector<float> angles, std::vector<Axis> axis);
private:
  std::vector<std::shared_ptr<threepp::Mesh>> bones;
};

#endif //CRANE_HPP
