#include "types.h"
/* insmenu 0x004F0540 (pass-27 window) -- `c.le.s $f0, $f1` + `bc1f` is
 * `> 0.0f`, returned as 0/1.  The return is s32, NOT u8: a u8 return
 * adds `andi $2, $2, 0xFF` after the epilogue load.  Shape-identical to
 * the matched insmenu_InsectVsConfirmDialogIsVisible_4ee860. */
extern const u8 D_004FA180[];
extern f32 func_290770(const void *a, s32 b);
s32 insmenu_InsectVsRegPwPanelIsVisible_4f0540(void) { return func_290770(D_004FA180, 0x4C) > 0.0f; }
