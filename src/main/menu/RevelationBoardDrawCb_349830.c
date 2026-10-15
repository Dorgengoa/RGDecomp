#include "types.h"

extern void RevelationBoardDraw_349e70(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047F6C4;
extern s32 D_00482360;
extern s32 D_0048238C;
extern s16 D_00482E28;

s32 RevelationBoardDrawCb_349830(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 t0;
    s32 t1;
    s16 t2;
    s32 t3;

    if (p4 != 0) {
        t0 = D_0047F6C4;
        t1 = D_0048238C;
        RevelationBoardDraw_349e70(t1, t0, p2, p3);
        t2 = D_00482E28;
        if (t2 == 2) {
            t3 = D_00482360;
            UiSetWidgetsVisibleById_291110(t3, 0x53, 0, 1);
        }
    }
    return 1;
}
