#include "types.h"
/* insmenu 0x004EE710 -- `func_290770(D_004FA180, 9) >= 1.0f`, returned as 0/1.  ⚠ The return type is s32, NOT u8:
 * a u8 return makes mwcc add `andi $2, $2, 0xFF` after the epilogue load, one
 * word retail does not have.  Measured, both ways.
 * MIPS has no c.ge.s, so `>=` is `c.lt.s` + `bc1f`, which is exactly retail's
 * shape; the 1.0f is materialised inline as lui 0x3F80 / mtc1. */
extern const u8 D_004FA180[];
extern f32 func_290770(const void *a, s32 b);
s32 insmenu_InsectVsYesNoCursorIsOpaque_4ee710(void) { return func_290770(D_004FA180, 9) >= 1.0f; }
