/* rgp:protos */
#define RGP_SELF_EventPushDesRecSlotMaybe_250450 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void Sprintf_1343b8(void *, void *, s32);
/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045ED48[];
extern s32 D_00481F2C;

struct Obj0;

struct Obj0 {
    s32 m00;
};

void * EventPushDesRecSlotMaybe_250450(s32 p0, s32 p1, struct Obj0 *p2)
{
    u128 v30[2];
    s32 t0;
    s32 r1;
    s32 t1;
    s32 t2;

    t0 = D_00481F2C;
    Sprintf_1343b8(v30, D_0045ED48, t0);
    r1 = RecStackPush_1c4240(p0, v30);
    p2->m00 = r1;
    t1 = D_00481F2C;
    D_00481F2C = (t1 + 1);
    if ((t1 + 1) > 0x2710) {
        D_00481F2C = 0;
    }
    t2 = p2->m00;
    return RecStackGetSlot_1c4330(p0, t2);
}
