/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegisterCursorHide_4f2190 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x4F2190 -- TAIL CALL `j func_2907A0` with a 0.0f third argument
 * (mtc1 $0, $f12).  The ABI numbers float and integer arguments
 * independently, so the f32 takes $f12 whatever its position in
 * the list.  insmenu_D_004FA180 is overlay data -> `const` -> %hi/%lo. */
extern u8 insmenu_D_004FA180[];
/*rgp*/
void insmenu_InsectVsRegisterCursorHide_4f2190(void) { UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x18, 0.0f); }
