#include "types.h"

extern void memset(void *, s32, s32);
extern void MesWinCopyText_272840(s32, void *);
extern void MesWinResetLayout_2729c0(void *);
extern void MesWinMeasureText_272b80(void *, void *);
extern void MesWinLoadText_273c70(void *, void *, s32);
typedef unsigned __int128 u128;

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
