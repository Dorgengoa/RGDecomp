#include "types.h"
/* insmenu 0x4F04F0 -- `func_290770(D_004FA180, 0x4C) <= 0.0f` returned as 0/1 through
 * c.le.s + bc1t.
 * The return type is s32, NOT u8: a u8 return adds
 * `andi $2, $2, 0xFF` after the epilogue load, one word retail
 * does not have.  Measured both ways on insmenu_InsectVsConfirmDialogIsHidden_4ee8a0. */
extern const u8 D_004FA180[];
extern f32 func_290770(const void *a, s32 b);
s32 insmenu_InsectVsRegPwPanelIsHidden_4f04f0(void) { return func_290770(D_004FA180, 0x4C) <= 0.0f; }
