#include "types.h"

/* insmenu 0x004F50B0 (88 bytes, 22 instructions, 3 calls) -- hand the two
 * pad banks to the list widget and return the caller's handle unchanged.
 *
 * The first parameter is UNUSED -- `$4` is overwritten with 0 for the first
 * call before anything reads it -- so the arity is not visible from inside.
 * It is written as two parameters because the returned value is `$5`, which
 * only a second parameter can be.
 */

extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];
extern const u8 D_004B2570;
extern const u8 D_004B27E0;

extern void func_37BAC0(s32 a);
extern void func_28E100(const void *a, const void *b, const void *c, s32 d);
extern void func_3774D0(const void *a);

void *insmenu_InsectVsTeamListTick_4f50b0(s32 unused, void *h)
{
    func_37BAC0(0);
    func_28E100(D_004FA1A0, (void *)&D_004B2570, (void *)&D_004B27E0, 0);
    func_3774D0(D_004FA180);
    return h;
}
