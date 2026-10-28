/* rgp:protos */
#define RGP_SELF_MenuTacticsHideAllPanels_357360 1
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
    u8 pad000[0x5C];
    s32 m5C;
};

s32 MenuTacticsHideAllPanels_357360(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 l4;
    s32 t4;
    s32 t5;
    s32 t6;
    s32 t7;
    s32 t8;
    s32 t9;

    t0 = p0->m5C;
    UiSetWidgetVisible_290010(t0, 0xBB, 0, -1);
    t1 = p0->m5C;
    UiSetWidgetVisible_290010(t1, 0x1A6, 0, -1);
    t2 = p0->m5C;
    UiSetWidgetsVisibleById_291110(t2, 0x38, 0, 1);
    t3 = p0->m5C;
    UiSetWidgetsVisibleById_291110(t3, 0x37, 0, 1);
    l4 = 0;
    do {
        t4 = p0->m5C;
        UiSetWidgetsVisibleById_291110(t4, ((l4 + 0xE9) & 0xFFFF), 0, 1);
        t5 = p0->m5C;
        UiSetWidgetsVisibleById_291110(t5, ((l4 + 0xF5) & 0xFFFF), 0, 1);
        t6 = p0->m5C;
        UiSetWidgetsVisibleById_291110(t6, ((l4 + 0xF8) & 0xFFFF), 0, 1);
        t7 = p0->m5C;
        UiSetWidgetsVisibleById_291110(t7, ((l4 + 0xEC) & 0xFFFF), 0, 1);
        t8 = p0->m5C;
        UiSetWidgetsVisibleById_291110(t8, ((l4 + 0xEF) & 0xFFFF), 0, 1);
        t9 = p0->m5C;
        UiSetWidgetsVisibleById_291110(t9, ((l4 + 0xF2) & 0xFFFF), 0, 1);
        l4 = (l4 + 1);
    } while (l4 < 3);
    return 1;
}
