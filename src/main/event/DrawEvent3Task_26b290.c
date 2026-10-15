#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern s32 MenuWinGetDrawLayer_26c280(s32);
extern s32 MenuWinUpdate_26bfe0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048206C;

void DrawEvent3Task_26b290(void)
{
    s32 r0;
    s32 l1;
    s32 t0;
    s32 r2;
    s32 rv4;
    s32 t1;
    s32 r3;

    r0 = GetCurrentScene_1f5be0();
    l1 = 0;
    do {
        t0 = D_0048206C;
        r2 = MenuWinGetDrawLayer_26c280((t0 + (((l1 << 3) - l1) << 5)));
        rv4 = r2;
        if (r2 == 2) {
            t1 = D_0048206C;
            r3 = MenuWinUpdate_26bfe0((t1 + (((l1 << 3) - l1) << 5)), r0);
            rv4 = r3;
        }
        l1 = (l1 + 1);
    } while (l1 < 8);
}
