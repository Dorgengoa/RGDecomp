/* rgp:protos */
#define RGP_SELF_EventCastSetObjFlags_257b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481F78;

s32 EventCastSetObjFlags_257b10(s32 p0, s32 p1, s32 p2)
{
    s32 t0;
    s32 t1;
    s32 r0;

    t0 = D_00481F78;
    t1 = *(s32 *)((u8 *)(p1 << 4) + p0 + 0x4);
    r0 = ((s32)ObjRecSetFlags_1c3e00(t0, 1, t1, p2));
    return 1;
}
