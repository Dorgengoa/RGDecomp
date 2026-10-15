#include "types.h"
/* insmenu 0x004EE8A0 -- `func_290770(D_004FA180, 6) <= 0.0f`, returned as 0/1.  ⚠ The return type is s32, NOT u8:
 * a u8 return makes mwcc add `andi $2, $2, 0xFF` after the epilogue load, one
 * word retail does not have.  Measured, both ways.
 *   mtc1 $0, $f1 / c.le.s $f0, $f1 / bc1t <ret 1> / daddu $2, $0, $0
 * The 0.0f is an inline literal (mtc1 from $0), not a named float-pool global.
 * D_004FA180 is overlay data -> `const` -> %hi/%lo. */
extern const u8 D_004FA180[];
extern f32 func_290770(const void *a, s32 b);
s32 insmenu_InsectVsConfirmDialogIsHidden_4ee8a0(void) { return func_290770(D_004FA180, 6) <= 0.0f; }
