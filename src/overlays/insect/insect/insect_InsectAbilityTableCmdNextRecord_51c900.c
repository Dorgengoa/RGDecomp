#include "types.h"
/* insect 0x0051C900 -- pass-28 unnamed-listing conversion.  D_00485170 is
 * _gp+0x0 and inside the gp window, so it stays plain; the same global
 * insect_InsectAbilityTableCmdResistType_51cac0 guards the same way.  The `bnel` guard is the
 * null-context early return and the s32 result is the "context was there"
 * predicate. */
typedef struct Ctx {
    u8 pad00[0x58];
    s32 m58;           /* +0x58 */
    u8 pad5C[0x64 - 0x5C];
    s32 m64;           /* +0x64 */
    s32 m68;           /* +0x68 */
} Ctx;

extern Ctx *D_00485170;

s32 insect_InsectAbilityTableCmdNextRecord_51c900(void)
{
    Ctx *g;

    g = D_00485170;
    if (g == 0) {
        return 0;
    }
    g->m68 = g->m68 + 1;
    g->m64 = g->m58 + g->m68 * 128;
    return 1;
}
