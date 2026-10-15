#include "types.h"
/* insmenu 0x4EE8E0 -- `func_290770(D_004FA180, 0x6) >= 1.0f` returned as 0/1 through
 * c.lt.s + bc1f.
 * The return type is s32, NOT u8: a u8 return adds
 * `andi $2, $2, 0xFF` after the epilogue load, one word retail
 * does not have.  Measured both ways on insmenu_InsectVsConfirmDialogIsHidden_4ee8a0. */
extern const u8 D_004FA180[];
extern f32 func_290770(const void *a, s32 b);
s32 insmenu_InsectVsConfirmDialogIsOpaque_4ee8e0(void) { return func_290770(D_004FA180, 0x6) >= 1.0f; }
