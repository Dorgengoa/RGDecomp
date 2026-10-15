#include "types.h"
/* insect 0x004EFF00 -- pass-28 unnamed-listing conversion.  The 0x004EFEE0
 * neighbour: same gp context global (D_00484F58, _gp-0x218, plain), a
 * different field, and a clear instead of an increment. */
typedef struct Ctx {
    u8 pad00[0xC];
    s32 mC;            /* +0x0C */
} Ctx;

extern Ctx *D_00484F58;

s32 insect_InsectFormationParseFormation_4eff00(void)
{
    D_00484F58->mC = 0;
    return 1;
}
