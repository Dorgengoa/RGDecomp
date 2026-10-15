#include "types.h"

/* insmenu 0x004F6AC0 (200 bytes) -- walk the widget-id table and set each
 * entry's alpha or its colour according to the mode.
 *
 * ★ The id is a `u16` LOCAL, and its `andi $5, $3, 0xFFFF` -- the narrow
 * store's own normalisation, not the callee's parameter -- is what fills the
 * FIRST guard's delay slot.  Inlined at the three call sites instead, mwcc has
 * nothing to sink there, converts that guard to its LIKELY form and the unit is
 * a word SHORT.  The table terminator is the loop condition and the same `lhu`.
 * ★ `mtc1 $0, $f12` is the literal `0.0f`; `lui 0x3F800000` / `lui 0xBF800000`
 * are `1.0f` and `-1.0f`. */

extern const u8 D_004FA180[];
extern const u16 D_004FA030[];
extern f32 D_0047D3C0;          /* gp - 0x7DB0 */

extern void func_2907A0(const void *a, u16 id, f32 v);
extern void func_290690(const void *a, u16 id, f32 x, f32 y, f32 z);

void insmenu_InsectVsLoadWidgetsFade_4f6ac0(s32 mode)
{
    s32 i;
    u16 id;

    i = 0;
    while (D_004FA030[i] != 0) {
        id = D_004FA030[i];
        if (mode == 0) {
            func_2907A0(D_004FA180, id, 0.0f);
        } else if (mode == 1) {
            func_290690(D_004FA180, id, 1.0f, D_0047D3C0, -1.0f);
        } else if (mode == 2) {
            func_290690(D_004FA180, id, 0.0f, D_0047D3C0, -1.0f);
        }
        i++;
    }
}
