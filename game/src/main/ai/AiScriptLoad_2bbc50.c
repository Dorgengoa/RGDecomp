/* rgp:protos */
#define RGP_SELF_AiScriptLoad_2bbc50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xB0];
    s16 mB0;
    s16 mB2;
    u8 pad0B4[0x4];
    s32 mB8;
};

void AiScriptLoad_2bbc50(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    u128 v60[6];
    s32 rv0;
    struct Obj0 * rv1;
    s32 t0;
    s32 t1;

    rv0 = 1;
    rv1 = p0;
    if (p4 == 1) {
        t0 = p0->mB8;
        p0->mB8 = (t0 | 4);
        p0->mB0 = -1;
        p0->mB2 = -1;
        rv0 = -1;
        rv1 = (struct Obj0 *)((u8 *)p0 + 0x54);
    }
    MemStackCtor_14e030(v60);
    MemStackInit_14d810(v60, p2, p3);
    AiScriptVmSetup_2c1690(rv1, p1, v60);
    t1 = p0->mB8;
    p0->mB8 = (t1 | 1);
}
