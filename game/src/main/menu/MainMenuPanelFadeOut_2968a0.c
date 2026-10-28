/* rgp:protos */
#define RGP_SELF_MainMenuPanelFadeOut_2968a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN MainMenuPanelFadeOut_2968a0 -- window 0x00296000-0x0029C000, sibling of the
   MainMenuInit_297510 registration list.  Zero branches: a straight-line list of
   eight calls against the single panel handle D_004DB1B0, then `return 1`.

   The float "globals" at 0x0047D684 / 0x0047D7B4 / 0x0047D7B8 are read as
   externs, not written as literals: that is the settled MAIN spelling (every
   byte-identical main unit that touches the 0x0047Dxxx region uses
   `extern f32`), and the values are -0.15 / 0.1 / -0.3.  1.0f and -1.0f are
   inline (lui + mtc1), which is what mwcc does for a representable constant.

   UiFadeWidgetAlpha_290690(handle, id, f32, f32, f32)   -- $4 $5 / $f12 $f13 $f14
   UiMoveWidgetUniform_290f50(handle, id, s32, s32, s32, f32) -- $4..$8 / $f12
   prototypes taken from the byte-identical src/p23c and src/qz units.  */

extern u8 D_004DB1B0[];

extern f32 D_0047D684;
extern f32 D_0047D7B4;
extern f32 D_0047D7B8;

/*rgp*/
/*rgp*/
/*rgp*/

s32 MainMenuPanelFadeOut_2968a0(void)
{
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x33, 0, 1);
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x32, 0, 1);
    UiFadeWidgetAlpha_290690(D_004DB1B0, 1, 0.0f, D_0047D684, 1.0f);
    UiFadeWidgetAlpha_290690(D_004DB1B0, 9, 0.0f, D_0047D7B8, -1.0f);
    UiFadeWidgetAlpha_290690(D_004DB1B0, 0xA, 0.0f, D_0047D684, -1.0f);
    UiMoveWidgetUniform_290f50(D_004DB1B0, 0xB, -0x30, -0xF, D_0047D7B4, 0);
    UiFadeWidgetAlpha_290690(D_004DB1B0, 0xB, 0.0f, D_0047D684, -1.0f);
    UiFadeWidgetAlpha_290690(D_004DB1B0, 7, 0.0f, D_0047D684, -1.0f);
    return 1;
}
