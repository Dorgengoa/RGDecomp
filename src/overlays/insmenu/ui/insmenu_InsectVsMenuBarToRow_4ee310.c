#include "types.h"
/* insmenu 0x004EE310 -- one call, argument 4 is o->field12 * 57 built by
 * shifts (`x*8 - x` then `*8` then `+x`).  The colour argument is
 * masked with `andi $5, $6, 0xFFFF`, so the cast is at the CALL.
 *
 * The second parameter is never read -- $5 is overwritten by the
 * mask before any use.  There is no caller inside the overlay, so
 * the slot's type is unconstrained; s32 keeps the third parameter
 * in $6, which the mask proves. */
typedef struct {
    u8 pad00[0x12];
    s16 field12;
} Widget;

extern const u8 D_004FA180[];
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
s32 insmenu_InsectVsMenuBarToRow_4ee310(Widget *o, s32 unused, s32 colour)
{
    func_290F60(D_004FA180, (u16)colour, 0, o->field12 * 57);
    return 1;
}
