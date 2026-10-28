/* rgp:protos */
#define RGP_SELF_GetQuadrantAngle_324120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

f32 GetQuadrantAngle_324120(void *rgp_a0)
{
    return 90.0f * (f32)AngleToQuadrant_323fd0((void *)rgp_a0);
}
