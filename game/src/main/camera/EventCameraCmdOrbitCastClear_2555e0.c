/* rgp:protos */
#define RGP_SELF_EventCameraCmdOrbitCastClear_2555e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strcpy(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

extern u8 D_0045EDA0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x7C];
    s32 m7C;
    s32 m80;
    s32 m84;
    u8 pad088[0x8];
    u128 m90;
    s32 mA0;
    s32 mA4;
    s32 mA8;
};

s32 EventCameraCmdOrbitCastClear_2555e0(s32 p0, struct Obj0 *p1)
{
    s32 r0;

    p1->m7C = 0;
    p1->m80 = 0;
    p1->m84 = 0;
    p1->m90 = 0;
    p1->mA0 = 0;
    p1->mA4 = 0;
    p1->mA8 = 0;
    r0 = ((s32)strcpy((struct Obj0 *)((u8 *)p1 + 0xAC), D_0045EDA0));
    return 0;
}
