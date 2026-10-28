/* rgp:protos */
#define RGP_SELF_AiCmdCameraFollowSetTargetMode_2c2d50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x44];
    s32 m44;
};

s32 AiCmdCameraFollowSetTargetMode_2c2d50(s32 p0, s32 p1)
{
    s32 rv3;
    struct Obj0 *r0;
    s32 rv2;
    s32 r1;

    rv3 = rv2;
    if (p1 != 1) {
        rv3 = 0;
    } else {
        r0 = GetCameraFollowParams_1f6d80();
        rv2 = 1;
        if (r0 == 0) {
            rv2 = 0;
        } else {
            r1 = ScriptSlotGetInt_2cc9c0(p0);
            r0->m44 = r1;
            rv2 = 1;
        }
        rv3 = rv2;
    }
    return rv3;
}
