/* rgp:protos */
#define RGP_SELF_CameraSetClampEaseDivMaybe_161e10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the small-data f32 D_00481118. */

extern f32 D_00481118;

void CameraSetClampEaseDivMaybe_161e10(f32 value)
{
    D_00481118 = value;
}
