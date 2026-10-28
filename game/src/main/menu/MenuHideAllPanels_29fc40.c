/* rgp:protos */
#define RGP_SELF_MenuHideAllPanels_29fc40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4C4];
    s32 m4C4;
};

s32 MenuHideAllPanels_29fc40(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 t5;
    s32 l6;
    s32 t6;
    s32 l8;
    s32 t7;
    s32 t8;
    s32 t9;
    s32 t10;
    s32 t11;
    s32 t12;
    s32 l15;
    s32 t13;
    s32 t14;
    s32 t15;
    s32 t16;
    s32 t17;
    s32 t18;

    t0 = p0->m4C4;
    UiSetWidgetVisible_290010(t0, 0xB6, 0, -1);
    t1 = p0->m4C4;
    UiSetWidgetVisible_290010(t1, 0x1A9, 0, -1);
    t2 = p0->m4C4;
    UiSetWidgetVisible_290010(t2, 0x151, 0, -1);
    t3 = p0->m4C4;
    UiSetWidgetVisible_290010(t3, 0x118, 0, -1);
    t4 = p0->m4C4;
    UiSetWidgetsVisibleById_291110(t4, 0x183, 0, 1);
    t5 = p0->m4C4;
    UiSetWidgetsVisibleById_291110(t5, 0x180, 0, 1);
    l6 = 0;
    do {
        t6 = p0->m4C4;
        UiSetWidgetsVisibleById_291110(t6, ((l6 + 0x11B) & 0xFFFF), 0, 1);
        l6 = (l6 + 1);
    } while (l6 < 4);
    l8 = 0;
    do {
        t7 = p0->m4C4;
        UiSetWidgetsVisibleById_291110(t7, ((l8 + 0xE9) & 0xFFFF), 0, 1);
        t8 = p0->m4C4;
        UiSetWidgetsVisibleById_291110(t8, ((l8 + 0xF5) & 0xFFFF), 0, 1);
        t9 = p0->m4C4;
        UiSetWidgetsVisibleById_291110(t9, ((l8 + 0xF8) & 0xFFFF), 0, 1);
        t10 = p0->m4C4;
        UiSetWidgetsVisibleById_291110(t10, ((l8 + 0xEC) & 0xFFFF), 0, 1);
        t11 = p0->m4C4;
        UiSetWidgetsVisibleById_291110(t11, ((l8 + 0xEF) & 0xFFFF), 0, 1);
        t12 = p0->m4C4;
        UiSetWidgetsVisibleById_291110(t12, ((l8 + 0xF2) & 0xFFFF), 0, 1);
        l8 = (l8 + 1);
    } while (l8 < 3);
    l15 = 0;
    do {
        t13 = p0->m4C4;
        UiSetWidgetsVisibleById_291110(t13, ((l15 + 0xFB) & 0xFFFF), 0, 1);
        t14 = p0->m4C4;
        UiSetWidgetsVisibleById_291110(t14, ((l15 + 0x105) & 0xFFFF), 0, 1);
        t15 = p0->m4C4;
        UiSetWidgetsVisibleById_291110(t15, ((l15 + 0x10C) & 0xFFFF), 0, 1);
        l15 = (l15 + 1);
    } while (l15 < 7);
    t16 = p0->m4C4;
    UiSetWidgetsVisibleById_291110(t16, 0x104, 0, 1);
    t17 = p0->m4C4;
    UiSetWidgetsVisibleById_291110(t17, 0x103, 0, 1);
    t18 = p0->m4C4;
    UiSetWidgetsVisibleById_291110(t18, 0x102, 0, 1);
    return 1;
}
