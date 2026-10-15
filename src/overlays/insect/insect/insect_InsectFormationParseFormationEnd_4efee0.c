#include "types.h"
/* insect 0x004EFEE0 -- pass-28 unnamed-listing conversion.  D_00484F58 is at
 * _gp-0x218 and so INSIDE the gp window 0x47D170..0x48D170; it must stay
 * plain (a `const` here would lose %gp_rel).  It is the same script-runner
 * context global insect_InsectFormationParseScript_4efde0 publishes. */
typedef struct Ctx {
    u8 pad00[0x10];
    s32 m10;           /* +0x10 */
} Ctx;

extern Ctx *D_00484F58;

s32 insect_InsectFormationParseFormationEnd_4efee0(void)
{
    Ctx *g;

    g = D_00484F58;
    g->m10 = g->m10 + 1;
    return 1;
}
