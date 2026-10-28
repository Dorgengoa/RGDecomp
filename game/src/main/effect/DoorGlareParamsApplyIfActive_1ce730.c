/* rgp:protos */
#define RGP_SELF_DoorGlareParamsApplyIfActive_1ce730 1
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
    u8 pad000[0x30];
    s32 m30;
};

void DoorGlareParamsApplyIfActive_1ce730(struct Obj0 *p0, s32 p1)
{
    s32 t0;

    t0 = p0->m30;
    if (t0 != 0) {
        DoorGlareParamsApply_1ce800(p0, p1);
    }
}
