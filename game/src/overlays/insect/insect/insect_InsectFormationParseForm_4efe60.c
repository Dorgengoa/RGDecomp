/* rgp:protos */
#define RGP_SELF_insect_InsectFormationParseForm_4efe60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vm_slot.h"
/* insect 0x004EFE60 -- 128 bytes.  A script native: two operands are pulled
 * off the VM stack with `func_15F780(v++)`, the context global D_00484F58
 * (_gp-0x218, inside the gp window, so it stays a PLAIN extern) is looked up
 * and re-loaded after the call, and the program counter at +0xC is bumped. */

typedef struct Ctx {
    u8  pad00[0xC];
    s32 mC;                         /* +0x0C */
    s32 m10;                        /* +0x10 */
} Ctx;

extern Ctx *D_00484F58;
/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectFormationParseForm_4efe60(Slot *v)
{
    Ctx  *g;
    void *e;
    s32   b;
    s32   a;

    a = VariantGetInt_15f780(v++);
    b = VariantGetInt_15f780(v);
    g = D_00484F58;
    e = insect_InsectFormationGetRow_4efdc0(g, g->m10);
    if (e != 0) {
        insect_InsectFormationSetCell_4f0010(e, D_00484F58->mC, b, a);
    }
    D_00484F58->mC = D_00484F58->mC + 1;
    return 1;
}
