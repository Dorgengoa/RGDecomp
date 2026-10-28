/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsBackGuideHide_4ea000 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EA000 -- TAIL CALL `j func_290690` with five arguments.
 * D_0047D3D8 is gp - 0x7D98, inside the gp window, so it is NOT const; the
 * 0.0f and -1.0f are inline literals. */
extern u8 insmenu_D_004FA180[];
extern f32 D_0047D3D8;
/*rgp*/
void insmenu_InsectVsBackGuideHide_4ea000(void) { UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x59, 0.0f, D_0047D3D8, -1.0f); }
