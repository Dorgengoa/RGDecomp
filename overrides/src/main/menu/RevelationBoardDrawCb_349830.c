/* rg-override: replaces game/src/main/menu/RevelationBoardDrawCb_349830.c sha256 5fa4fd9a28468e53bd812507eaa2851d1d8ebace3701a4a8d5974008b4037aa5
 * why: menu position (docs/WIDESCREEN.md "Revelation board on a wide screen", 2026-11-10 menuleft): the board's cells are drawn inside rg_layout_wide_begin / _end, so with $RG_REV_WIDE >= 1 the cells past the 4:3 screen's right edge show in the wide canvas instead of being hidden (presentation only; a no-op otherwise) */
/* rgp:protos */
#define RGP_SELF_RevelationBoardDrawCb_349830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
void rg_layout_wide_begin(void);
void rg_layout_wide_end(void);

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
        rg_layout_wide_begin();
        RevelationBoardDraw_349e70(t1, t0, p2, p3);
        rg_layout_wide_end();
        t2 = D_00482E28;
        if (t2 == 2) {
            t3 = D_00482360;
            UiSetWidgetsVisibleById_291110(t3, 0x53, 0, 1);
        }
    }
    return 1;
}
