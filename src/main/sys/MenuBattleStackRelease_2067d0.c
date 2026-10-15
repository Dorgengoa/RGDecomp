#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern void HeapHandleFree_1cdae0(s32, s32);
extern void MemStackClear_14dff0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481BCC;
extern u8 D_004BBC80[];
extern const s32 D_004BBCA8;

void MenuBattleStackRelease_2067d0(void)
{
    s32 t0;
    s32 r0;
    s32 t1;

    t0 = D_00481BCC;
    if (t0 != 0) {
        r0 = GetLoaderMgr_1f59d0();
        t1 = D_004BBCA8;
        HeapHandleFree_1cdae0(r0, t1);
        MemStackClear_14dff0(D_004BBC80);
        D_00481BCC = 0;
    }
}
