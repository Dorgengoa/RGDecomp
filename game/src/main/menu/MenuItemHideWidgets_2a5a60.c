/* rgp:protos */
#define RGP_SELF_MenuItemHideWidgets_2a5a60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00450DF0[];
extern u8 D_00450E10[];

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 MenuItemHideWidgets_2a5a60(struct Obj0 *p0)
{
    s32 l0;
    s32 t0;
    s32 l2;
    s32 t1;
    s32 l4;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 t5;
    s32 t6;
    s32 t7;

    l0 = 0;
    while (*(u16 *)((u8 *)D_00450DF0 + ((s16)l0 << 1)) != 0) {
        t0 = p0->m00;
        UiSetWidgetVisible_290010(t0, *(u16 *)((u8 *)D_00450DF0 + ((s16)l0 << 1)), 0, -1);
        l0 = (s16)(l0 + 1);
    }
    l2 = 0;
    while (*(u16 *)((u8 *)D_00450E10 + ((s16)l2 << 1)) != 0) {
        t1 = p0->m00;
        UiSetWidgetsVisibleById_291110(t1, *(u16 *)((u8 *)D_00450E10 + ((s16)l2 << 1)), 0, 1);
        l2 = (s16)(l2 + 1);
    }
    l4 = 0;
    do {
        t2 = p0->m00;
        UiSetWidgetsVisibleById_291110(t2, ((s16)(l4 + 0xFB) & 0xFFFF), 0, 1);
        t3 = p0->m00;
        UiSetWidgetsVisibleById_291110(t3, ((s16)(l4 + 0x105) & 0xFFFF), 0, 1);
        t4 = p0->m00;
        UiSetWidgetsVisibleById_291110(t4, ((s16)(l4 + 0x10C) & 0xFFFF), 0, 1);
        l4 = (l4 + 1);
    } while (l4 < 7);
    t5 = p0->m00;
    UiSetWidgetsVisibleById_291110(t5, 0x104, 0, 1);
    t6 = p0->m00;
    UiSetWidgetsVisibleById_291110(t6, 0x103, 0, 1);
    t7 = p0->m00;
    UiSetWidgetsVisibleById_291110(t7, 0x102, 0, 1);
    return 1;
}
