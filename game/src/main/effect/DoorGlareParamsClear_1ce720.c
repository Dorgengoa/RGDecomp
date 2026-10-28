/* rgp:protos */
#define RGP_SELF_DoorGlareParamsClear_1ce720 1
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
    u8 pad000[0x2C];
    s32 m2C;
    s32 m30;
};

void DoorGlareParamsClear_1ce720(struct Obj0 *p0, s32 p1)
{
    p0->m30 = 0;
    p0->m2C = 0;
    DoorGlareParamsApply_1ce800(p0, p1);
}
