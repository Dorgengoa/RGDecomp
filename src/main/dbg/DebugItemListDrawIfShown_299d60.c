#include "types.h"

extern void UiSetWidgetsVisibleById_291110(void *, s32, s32, s32);
extern void DebugItemListDraw_299500(void *);
extern void DebugItemListShowIcon_299980(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004DB1B0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x1B];
    u8 m1B;
};

void DebugItemListDrawIfShown_299d60(struct Obj0 *p0)
{
    u8 t0;

    t0 = p0->m1B;
    if (t0 == 0) {
        UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x1CF, 0, 1);
        return;
    }
    DebugItemListDraw_299500(p0);
    DebugItemListShowIcon_299980(p0);
}
