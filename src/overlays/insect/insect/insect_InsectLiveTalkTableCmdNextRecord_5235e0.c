#include "types.h"
/* insect 0x005235E0 -- pass-28 unnamed-listing conversion.  Same shape as
 * 0x004EFEE0 against the OTHER context global: D_00485208 is at _gp+0x98,
 * also inside the gp window, and is the one insect_InsectLiveTalkTableLoad_523540 runs its
 * {opcode, handler} table out of (+0x0C is that record count). */
typedef struct Ctx {
    u8 pad00[0xC];
    s32 mC;            /* +0x0C */
} Ctx;

extern Ctx *D_00485208;

s32 insect_InsectLiveTalkTableCmdNextRecord_5235e0(void)
{
    Ctx *g;

    g = D_00485208;
    g->mC = g->mC + 1;
    return 1;
}
