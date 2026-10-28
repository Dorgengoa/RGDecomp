/* rgp:protos */
#define RGP_SELF_CameraModeSetupMaybe_308df0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x15C];
    s32 m15C;
    s32 m160;
};

void CameraModeSetupMaybe_308df0(struct Obj0 *p0)
{
    CameraResetParams_3090a0(p0);
    p0->m15C = 0x42700000;
    p0->m160 = 0x42A00000;
}
