#include "types.h"
/* insmenu 0x004EE250 -- one call, argument 4 is o->f12 * 57 built by shifts
 * (`x*8 - x` then `*8` then `+x`).  The colour argument is masked with
 * `andi $5, $6, 0xFFFF`, so the cast is at the CALL, not at the parameter.
 *
 * ⚠ The second parameter is never read -- $5 is overwritten by the mask
 * before any use.  There is no caller inside the overlay (it is reached from
 * the main image), so the slot's type is unconstrained; `s32` is written to
 * keep the third parameter in $6, which the mask proves. */
extern const u8 D_004FA180[];
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
s32 insmenu_InsectVsMenuBarToRow_4ee250(void *o, s32 unused, s32 colour)
{
    func_290F60(D_004FA180, (u16)colour, 0, *(s16 *)((u8 *)o + 0x12) * 57);
    return 1;
}
