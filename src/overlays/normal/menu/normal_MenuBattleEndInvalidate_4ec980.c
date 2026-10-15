#include "types.h"
/* normal 0x004EC980 -- `addiu $3, $0, -1 / jr $31 / sw $3, 0($4)`.  Stores -1
 * through its pointer argument; the constant is materialised in $3 rather than
 * $2, so nothing is returned.  Renamed from `insmenu_InsectVsRegSaveCursorMoveCb_4ec980` (SESSION 57,
 * 2026-09-15, scripts/n_rename.py): that name collided with insmenu's own
 * `insmenu_InsectVsRegSaveCursorMoveCb_4ec980` at the same vram, and `rgd.src_path()` resolves by BASENAME
 * across all of src/, so insmenu's file always won the build regardless of
 * which overlay was being linked -- see [[levers.d/normal-unnamed-text]]. */
void normal_MenuBattleEndInvalidate_4ec980(s32 *p)
{
    *p = -1;
}
