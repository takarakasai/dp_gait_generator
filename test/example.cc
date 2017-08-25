
#include "dp_gait_generator/dp_gait_generator.h"

int main(void) {

  Dp::Gait ipos = {
    {+0.15, +0.08, -0.20}, {+0.15, -0.08, -0.20},
    {-0.15, +0.08, -0.20}, {-0.15, -0.08, -0.20},
    { 0.00,  0.00,  0.00},
    Dp::NONE,
  };
  Dp::GaitGenerator ggen(ipos);

  const Dp::Gaits& gaits = ggen.GenerateWalk({0.05, 0.0, 0.0}, 10);

  Dp::DebugDump(gaits);

  return 0;
}
