
#include "dp_gait_generator/dp_gait_generator.h"

#include <iostream>

int main(void) {

  Dp::Gait ipos = {
    {+0.15, +0.08, -0.20}, {+0.15, -0.08, -0.20},
    {-0.15, +0.08, -0.20}, {-0.15, -0.08, -0.20},
    { 0.00,  0.00,  0.00},
    Dp::NONE,
  };
  Dp::GaitGenerator ggen(ipos);

  const Dp::Gaits& gaits = ggen.GenerateWalk({0.05, 0.0, 0.0}, 10);

  std::cout << "-----------------------------------" << std::endl;
  Dp::DebugDump(gaits);

  std::cout << "-----------------------------------" << std::endl;
  size_t count = 0;
  for (auto g : gaits) {
    std::cout << " -- [" << count++ << "]" << std::endl;
    Dp::DebugDump(g.LocalGait());
  }

  return 0;
}
