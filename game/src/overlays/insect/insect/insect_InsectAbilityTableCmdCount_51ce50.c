/* rgp:protos */
#define RGP_SELF_insect_InsectAbilityTableCmdCount_51ce50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051CE50 -- 72 bytes, 18 instructions.  D_00485170 is _gp+0x0 (see
 * insect_InsectAbilityTableCmdNextRecord_51c900.c) and is RE-READ three times -- there is no cached local. */

typedef struct Ctx {
    u8  pad00[0x60];
    s32 m60;                        /* +0x60 */
} Ctx;

extern Ctx *D_00485170;

/*rgp*/
/*rgp*/

s32 insect_InsectAbilityTableCmdCount_51ce50(void *rgp_a0)
{
    if (D_00485170 == 0) {
        return 0;
    }
    D_00485170->m60 = VariantGetInt_15f780((void *)rgp_a0);
    insect_InsectAbilityTableAllocRecords_51cf50(D_00485170, D_00485170->m60);
    return 1;
}
