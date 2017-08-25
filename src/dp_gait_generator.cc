
#include "dp_gait_generator/dp_gait_generator.h"

#include <iostream>

namespace Dp {

  const Vector3d GaitGenerator::zero_step_ = {0.0, 0.0, 0.0};

  Gait& operator+(Gait &left, const Gait &right) {
    left.fl += right.fl;
    left.fr += right.fr;
    left.bl += right.bl;
    left.br += right.br;

    left.cpos += right.cpos;

    left.swing = right.swing;

    return left;
  };

  Gait& operator+=(Gait &left, const Gait &right) {
    return left + right;
  };

  /* Gaits */

  Gait Gait::LocalGait() {
    Gait gait = {
      fl - cpos, fr - cpos,
      bl - cpos, br - cpos,
      {0.0, 0.0, 0.0},
      swing,
    };

    return std::move(gait);
  }

  void DebugDump(const Gait& gait) {
    using namespace std;
    std::cout << showpos << " STEP   : "  << ToString(gait.swing) << " ( " << gait.swing << " )" << std::endl;
    std::cout << showpos << "   CPOS : (" << gait.cpos[0] << ", " << gait.cpos[1] << ", " << gait.cpos[2] << ")" << std::endl;
    std::cout << showpos << "   FL/R : (" << gait.fl[0] << ", " << gait.fl[1] << ", " << gait.fl[2] << ")"
                         <<           "(" << gait.fr[0] << ", " << gait.fr[1] << ", " << gait.fr[2] << ")" << std::endl;
    std::cout << showpos << "   BL/R : (" << gait.bl[0] << ", " << gait.bl[1] << ", " << gait.bl[2] << ")"
                         <<           "(" << gait.br[0] << ", " << gait.br[1] << ", " << gait.br[2] << ")" << std::endl;

    return;
  }

  void DebugDump(const Gaits& gaits) {
    std::cout << "==== num : " << gaits.size() << std::endl;
    for (size_t i = 0; i < gaits.size(); i++) {
      std::cout << "====== " << i << " / " << gaits.size() - 1 << std::endl;
      DebugDump(gaits[i]);
    }

    return;
  }

  /* class GaitGenerator */

  GaitGenerator::GaitGenerator(Gait ipos, Vector3d bpos) {
    bpos_ = bpos;
    ipos_ = ipos;

    gaits_.clear();
    gaits_.reserve(20);

    return;
  }

  GaitGenerator::~GaitGenerator() {
    return;
  }

  const Gaits& GaitGenerator::GenerateWalk(Vector3d dstep, size_t nos /*num_of_steps*/) {
    gaits_.clear();

    Gait step = ipos_;
    gaits_.push_back(step);

    /*   -   -
     *     o
     *   -   -   */
    Gait dstep_cpos_harf = {
      zero_step_,  zero_step_,
      zero_step_,  zero_step_,
      dstep / 2.0,
      CPOS,
    };

    Gait dstep_cpos_full = {
      zero_step_,  zero_step_,
      zero_step_,  zero_step_,
      dstep,
      CPOS,
    };

    /*   o   -
     *     -
     *   -   o   */
    Gait dstep_flbr_harf = {
      dstep / 2.0, zero_step_,
      zero_step_,  dstep / 2.0,
      zero_step_,
      FLBR,
    };

    Gait dstep_flbr_full = {
      dstep,       zero_step_,
      zero_step_,  dstep,
      zero_step_,
      FLBR,
    };

    /*   -   o 
     *     -
     *   o   -   */
    Gait dstep_frbl_harf = {
      dstep / 2.0,  zero_step_,
      zero_step_,  dstep / 2.0,
      zero_step_,
      FRBL,
    };

    Gait dstep_frbl_full = {
      dstep,      zero_step_,
      zero_step_,      dstep,
      zero_step_,
      FRBL,
    };

    step += dstep_flbr_harf;
    gaits_.push_back(step);

    step += dstep_cpos_harf;
    gaits_.push_back(step);

    size_t count;
    for (count = 1; count < (nos - 1); count++) {
      if (count % 2) {
        step += dstep_flbr_full;
      } else {
        step += dstep_frbl_full;
      }
      gaits_.push_back(step);

      step += dstep_cpos_full;
      gaits_.push_back(step);
    }

    if (step.swing == FLBR) {
      step += dstep_frbl_harf;
    } else {
      step += dstep_flbr_harf;
    }
    gaits_.push_back(step);

    step += dstep_cpos_harf;
    gaits_.push_back(step);

    return gaits_;
  }
}
