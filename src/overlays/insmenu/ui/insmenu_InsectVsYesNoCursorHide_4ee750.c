#include "types.h"
/* insmenu 0x004EE750 -- tail call `j func_2907A0`, three arguments.
 * D_004FA180 is OVERLAY data at 0x004FA180, far outside the gp window
 * (0x47D170..0x48D170), so it MUST be `const` or mwcc emits one %gp_rel
 * instruction where retail has the lui/addiu pair -- and the link would then
 * die on GP offset overflow.
 * $f12 = 0.0f: the ABI numbers float and integer arguments independently, so
 * the f32 is the first float argument whatever its position in the list. */
extern const u8 D_004FA180[];
extern void func_2907A0(const void *a, s32 b, f32 t);
void insmenu_InsectVsYesNoCursorHide_4ee750(void) { func_2907A0(D_004FA180, 9, 0.0f); }
