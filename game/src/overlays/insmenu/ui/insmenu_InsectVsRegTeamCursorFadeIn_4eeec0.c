/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegTeamCursorFadeIn_4eeec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EEEC0 -- guarded five-argument call.
 * `bnel $2, $0, <epilogue>` carrying `ld $31` in its delay slot: the
 * guard exits to the shared epilogue, so the BODY is the == 0 arm.
 * $f12/$f13/$f14 are three separate float arguments; the literals are
 * inline (lui) while D_0047D34C is a gp float-pool global
 * (lwc1 off $28) and so is NOT const. */
/*rgp*/
extern u8 insmenu_D_004FA180[];
extern f32 D_0047D34C;
/*rgp*/
void insmenu_InsectVsRegTeamCursorFadeIn_4eeec0(void)
{
    if (insmenu_InsectVsRegTeamCursorIsOpaque_4eee10() == 0) {
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x58, 1.0f, D_0047D34C, -1.0f);
    }
}
