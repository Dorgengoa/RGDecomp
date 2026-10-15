#include "types.h"
/* insmenu 0x004F8E80 -- `beqz $5` branches AWAY, so the guarded call is the
 * FALL-THROUGH and the condition is `!= 0`.  $4 is never read.
 * 0x4B2570 and 0x4B27E0 are unsymbolised MAIN-IMAGE data addresses: written
 * as `&extern` they take %hi/%lo, which is what the listing has; a cast
 * integer constant would compile to lui/ORI and differ by one bit.
 * 0x88B9 does not fit a signed 16-bit immediate, hence `ori`. */
extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];
extern const u8 D_004B2570;
extern const u8 D_004B27E0;
extern void func_28EA90(const void *ctx, s32 id, s32 a);
extern void func_37BAC0(s32 a);
extern s32 func_28E100(const void *a, const void *b, const void *c, s32 d);
extern void func_3774D0(const void *a);

s32 insmenu_InsectVsLoadPortTick_4f8e80(s32 unused, s32 a)
{
    if (a != 0) {
        func_28EA90(D_004FA1A0, 0x88B9, 0);
    }
    func_37BAC0(0);
    func_28E100(D_004FA1A0, &D_004B2570, &D_004B27E0, 0);
    func_3774D0(D_004FA180);
    return 1;
}
