/* rgp:protos */
#define RGP_SELF_EffectResSetName_2e2dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void strcpy(void *, s32);
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x50];
    s16 m50;
};

s32 EffectResSetName_2e2dc0(s32 p0, struct Obj0 *p1, s32 p2)
{
    s32 r1;

    strcpy((struct Obj0 *)((u8 *)p1 + 0x30), p2);
    r1 = ((unsigned short)NameHash16_2e3470(p2));
    p1->m50 = r1;
    return r1;
}
