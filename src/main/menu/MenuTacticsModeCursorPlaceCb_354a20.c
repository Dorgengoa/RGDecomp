#include "types.h"

extern s32 MenuGridCursorRequestSe_28e9e0(s32, s32);
extern s32 UiSetWidgetPos_290f60(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482364;
extern s32 D_0048236C;

struct Obj0;

struct Obj0 {
    u8 pad000[0x12];
    s16 m12;
};

s32 MenuTacticsModeCursorPlaceCb_354a20(struct Obj0 *p0)
{
    s32 t0;
    s32 r0;
    s16 t1;
    s32 t2;
    s32 r1;

    t0 = D_00482364;
    r0 = MenuGridCursorRequestSe_28e9e0(t0, 0);
    t1 = p0->m12;
    t2 = D_0048236C;
    r1 = UiSetWidgetPos_290f60(t2, 2, 7, (((t1 * 0x5) + (t1 * 0x14)) + 6));
    return 1;
}
