/* rgp:protos */
#define RGP_SELF_MenuItemTabsAvailUpdate_2b0070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482360;

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
    u8 pad014[0x4];
    s32 m18;
};

void MenuItemTabsAvailUpdate_2b0070(void)
{
    struct Obj0 *r0;
    s32 t0;
    s32 r1;
    s32 rv4;
    s32 rv5;
    s32 t1;
    s32 r2;
    s32 t2;
    s32 t3;
    s32 r3;
    s32 t4;
    s32 r6;
    s32 l7;
    s32 t5;
    s32 r8;
    s32 t6;
    s32 r9;

    r0 = GetGameData_1fede0();
    t0 = r0->m10;
    r1 = ((short)StateGetChapter_3cd5b0(t0));
    if (r1 >= 8) {
        t1 = D_00482360;
        r2 = ((s32)UiSetSpriteSizeUvSize_28f670(t1, 0x6D, 0x100, 0x12, 0x100, 0x12, 0x11));
        t2 = D_00482360;
        rv4 = r2;
        rv5 = t2;
    } else {
        t3 = D_00482360;
        r3 = ((s32)UiSetSpriteSizeUvSize_28f670(t3, 0x6D, 0, 0, 0, 0, 0x11));
        t4 = D_00482360;
        rv4 = r3;
        rv5 = t4;
    }
    r6 = ((s32)UiSetSpriteSizeUvSize_28f670(rv5, 0x6D, 0, 0, 0, 0, 0x12));
    l7 = 0;
    while (l7 < 8) {
        t5 = r0->m18;
        r8 = ((s32)InvFindByCategoryIndex_3c86e0(t5, 4, 0, l7, 0, 0));
        if (r8 != 0) {
            t6 = D_00482360;
            r9 = ((s32)UiSetSpriteSizeUvSize_28f670(t6, 0x6D, 0xA0, 0x12, 0xA0, 0x12, 0x12));
            return;
        }
        l7 = (l7 + 1);
    }
}
