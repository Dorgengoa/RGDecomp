/* rgp:protos */
#define RGP_SELF_MesWinSetText_2727b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void memset(void *, s32, s32);
/*rgp*/
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
    u8 pad000[0x194C];
    s32 m194C;
};

void MesWinSetText_2727b0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    u128 v40[50];

    if (p1 != 0) {
        memset(v40, 0, 0x320);
        MesWinCopyText_272840(p1, v40);
        p0->m194C = -2;
        MesWinResetLayout_2729c0(p0);
        MesWinMeasureText_272b80(p0, v40);
        MesWinLoadText_273c70(p0, v40, p3);
        return;
    }
}
