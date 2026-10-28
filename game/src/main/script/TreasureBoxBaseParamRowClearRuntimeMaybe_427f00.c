/* rgp:protos */
#define RGP_SELF_TreasureBoxBaseParamRowClearRuntimeMaybe_427f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x28];
    s32 m28;
    s32 m2C;
    u8 pad030[0x4];
    s32 m34;
    s32 m38;
    u8 pad03C[0x10];
    s32 m4C;
    s32 m50;
    s32 m54;
};

void TreasureBoxBaseParamRowClearRuntimeMaybe_427f00(struct Obj0 *p0)
{
    s32 l0;
    s32 l1;

    p0->m28 = 0;
    p0->m2C = 0;
    p0->m34 = 0;
    p0->m38 = 0;
    l1 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l1 << 2) + 0x40) = 0;
        l0 = ((l1 + 1) < 3);
        l1 = (l1 + 1);
    } while (l0 != 0);
    p0->m4C = 0;
    p0->m50 = 0;
    p0->m54 = 0;
}
