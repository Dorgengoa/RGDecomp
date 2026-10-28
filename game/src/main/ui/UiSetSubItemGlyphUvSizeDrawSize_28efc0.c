/* rgp:protos */
#define RGP_SELF_UiSetSubItemGlyphUvSizeDrawSize_28efc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x16];
    s16 m16;
    s16 m18;
    u8 pad01A[0x2];
    s16 m1C;
    s16 m1E;
};

struct Obj0 *UiSetSubItemGlyphUvSizeDrawSize_28efc0(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6)
{
    struct Obj0 *r0;

    r0 = UiGetWidgetSubItem_28f2b0(p0, p1, p6);
    if (r0 != 0) {
        if (p2 != -0x270F) {
            r0->m16 = p2;
        }
        if (p3 != -0x270F) {
            r0->m18 = p3;
        }
        if (p4 != -0x270F) {
            r0->m1C = p4;
        }
        if (p5 != -0x270F) {
            r0->m1E = p5;
        }
    }
    return r0;
}
