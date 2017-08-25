
#include <vector>

#include "dpcommon/dp_type.h"

namespace Dp {

  typedef enum {
    NONE,
    CPOS,
    FLBL,
    FLBR,
    FRBL,
    FRBR,
  }LEG_SWING_PATTERN;

  inline const char* ToString(LEG_SWING_PATTERN swing) {
    switch (swing) {
      case NONE: return "NONE";
      case CPOS: return "CPOS";
      case FLBL: return "FLBL";
      case FLBR: return "FLBR";
      case FRBL: return "FRBL";
      case FRBR: return "FRBR";
      default  : return "UNKNOWN";
    }
  }
 
  typedef struct {
    Vector3d fl;
    Vector3d fr;
    Vector3d bl;
    Vector3d br;

    Vector3d cpos;
    LEG_SWING_PATTERN swing;
  }Gait;

  typedef std::vector<Gait> Gaits;

  void DebugDump(const Gait& gait);
  void DebugDump(const Gaits& gaits);

  Gait& operator+(Gait &left, const Gait &right);
  Gait& operator+=(Gait &left, const Gait &right);

  class GaitGenerator {
    public:
      GaitGenerator(Gait ipos, Vector3d bpos = (Vector3d){0.0, 0.0, 0.0});
      virtual ~GaitGenerator();

      const Gaits& GenerateWalk(Vector3d dstep, size_t num_of_steps);

    private:
      //Vector3d dstep_;
      //size_t num_of_steps_;

      /* base link position at world coords */
      Vector3d bpos_;

      /* initial knee tip position at local coords */
      Gait ipos_;

      Gaits gaits_;

      static const Vector3d zero_step_;
  };
}
