/* rgp:protos */
#define RGP_SELF_MapModelEntryCtor_1956f0 1
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
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
};

struct Obj0 *MapModelEntryCtor_1956f0(struct Obj0 *p0)
{
    s32 r0;

    p0->m00 = 0;
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m18 = 0xBF800000;
    p0->m14 = 0xBF800000;
    p0->m1C = 0;
    p0->m0C = 0;
    p0->m10 = 0;
    r0 = (FarClipRecGetPresetFadeRates_186e70(0, (struct Obj0 *)((u8 *)p0 + 0x20), (struct Obj0 *)((u8 *)p0 + 0x24)), (s32)0);
    return p0;
}
