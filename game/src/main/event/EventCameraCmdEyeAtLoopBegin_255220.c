/* rgp:protos */
#define RGP_SELF_EventCameraCmdEyeAtLoopBegin_255220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x30];
    s32 m30;
};

s32 EventCameraCmdEyeAtLoopBegin_255220(s32 p0, struct Obj0 *p1)
{
    p1->m30 = p0;
    return 0;
}
