#include "types.h"

extern void * UiPageFindWidget_289b00(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
};

s32 UiPageGetWidgetSprites_289ad0(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s32 t0;

    r0 = UiPageFindWidget_289b00(p0, p1);
    if (r0 != 0) {
        t0 = r0->m20;
        return t0;
    }
    return 0;
}
