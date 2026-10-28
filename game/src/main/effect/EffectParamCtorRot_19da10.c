/* rgp:protos */
#define RGP_SELF_EffectParamCtorRot_19da10 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

extern u8 D_00470940[];
extern u8 D_00470A10[];
extern u8 D_00470E30[];

struct Obj0;

struct Obj0 {
    void *m00;
    s32 m04;
    u8 pad008[0x8];
    s32 m10;
    s32 m14;
    u8 pad018[0x8];
    u128 m20;
    u128 m30;
};

struct Obj0 *EffectParamCtorRot_19da10(struct Obj0 *p0)
{
    p0->m00 = D_00470E30;
    p0->m04 = -1;
    p0->m00 = D_00470A10;
    p0->m14 = 0;
    p0->m10 = 0;
    p0->m20 = 0;
    p0->m30 = 0;
    p0->m00 = D_00470940;
    return p0;
}
