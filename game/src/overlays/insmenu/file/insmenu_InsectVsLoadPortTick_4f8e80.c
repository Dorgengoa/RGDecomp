/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadPortTick_4f8e80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F8E80 -- `beqz $5` branches AWAY, so the guarded call is the
 * FALL-THROUGH and the condition is `!= 0`.  $4 is never read.
 * 0x4B2570 and 0x4B27E0 are unsymbolised MAIN-IMAGE data addresses: written
 * as `&extern` they take %hi/%lo, which is what the listing has; a cast
 * integer constant would compile to lui/ORI and differ by one bit.
 * 0x88B9 does not fit a signed 16-bit immediate, hence `ori`. */
extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];
extern u8 D_004B2570;
extern u8 D_004B27E0;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsLoadPortTick_4f8e80(s32 unused, s32 a)
{
    if (a != 0) {
        UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88B9, 0);
    }
    SaveStepAndGetStatus_37bac0(0);
    MenuGridCursorInputPad2_28e100(insmenu_D_004FA1A0, &D_004B2570, &D_004B27E0, 0);
    SaveProgressBarUpdate_3774d0(insmenu_D_004FA180);
    return 1;
}
