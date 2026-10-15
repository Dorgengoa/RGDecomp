#include "types.h"
/* insmenu 0x4F0330 -- TAIL CALL `j func_2907A0` with a 0.0f third argument
 * (mtc1 $0, $f12).  The ABI numbers float and integer arguments
 * independently, so the f32 takes $f12 whatever its position in
 * the list.  D_004FA180 is overlay data -> `const` -> %hi/%lo. */
extern const u8 D_004FA180[];
extern void func_2907A0(const void *a, s32 b, f32 t);
void insmenu_InsectVsRegPwCursorHide_4f0330(void) { func_2907A0(D_004FA180, 0x51, 0.0f); }
