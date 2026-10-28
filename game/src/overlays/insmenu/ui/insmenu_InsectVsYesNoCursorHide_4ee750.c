/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsYesNoCursorHide_4ee750 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EE750 -- tail call `j func_2907A0`, three arguments.
 * insmenu_D_004FA180 is OVERLAY data at 0x004FA180, far outside the gp window
 * (0x47D170..0x48D170), so it MUST be `const` or mwcc emits one %gp_rel
 * instruction where retail has the lui/addiu pair -- and the link would then
 * die on GP offset overflow.
 * $f12 = 0.0f: the ABI numbers float and integer arguments independently, so
 * the f32 is the first float argument whatever its position in the list. */
extern u8 insmenu_D_004FA180[];
/*rgp*/
void insmenu_InsectVsYesNoCursorHide_4ee750(void) { UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 9, 0.0f); }
