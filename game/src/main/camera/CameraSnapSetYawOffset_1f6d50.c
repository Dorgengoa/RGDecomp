/* rgp:protos */
#define RGP_SELF_CameraSnapSetYawOffset_1f6d50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the small-data f32 D_00481A20. */

extern f32 D_00481A20;

void CameraSnapSetYawOffset_1f6d50(f32 value)
{
    D_00481A20 = value;
}
