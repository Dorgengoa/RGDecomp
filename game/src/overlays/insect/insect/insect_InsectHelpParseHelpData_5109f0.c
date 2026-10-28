/* rgp:protos */
#define RGP_SELF_insect_InsectHelpParseHelpData_5109f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005109F0 -- 244 bytes.  A script-VM command body against the
 * context global D_00484FD0 (`lw $2, -0x1A0($28)`, the one 0x00510B30
 * publishes).  The argument cursor advances EIGHT bytes per read and every
 * increment sits in its call's delay slot, so each read is `f(p++)`; the last
 * increment is dead and mwcc drops it.  The context is RE-READ before each
 * dispatch rather than kept in a register.  The null guard is written as the
 * POSITIVE `if`, so the body FALLS THROUGH and the `return 0` sits at the
 * bottom; `if (c == 0) return 0;` inverts the branch and shifts the whole
 * body two words. */
typedef struct Arg { u8 raw[8]; } Arg;

typedef struct Ent {
    u8  pad00[4];
    s16 f4;                         /* +0x04 */
} Ent;

typedef struct Ctx {
    u8   pad00[4];
    s32  f4;                        /* +0x04 */
    u8   pad08[4];
    s32  fC;                        /* +0x0C */
} Ctx;

extern Ctx *D_00484FD0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectHelpParseHelpData_5109f0(Arg *p, s32 n)
{
    Ent *e;

    if (D_00484FD0 != 0) {
        e = ((Ent *)insect_InsectHelpGetEntryRaw_510bd0(D_00484FD0, VariantGetInt_15f780(p++)));
        VariantGetInt_15f780(p++);
        e->f4 = VariantGetInt_15f780(p++);
        insect_InsectHelpEntrySetTitle_510e80(e, D_00484FD0->f4, SlotGetInt_15f720(p++));
        insect_InsectHelpEntrySetBoardFile_510e20(e, D_00484FD0->f4, SlotGetInt_15f720(p++));
        if (n >= 4) {
            insect_InsectHelpEntrySetPageImage_510dc0(e, D_00484FD0->f4, SlotGetInt_15f720(p++));
        }
        D_00484FD0->fC++;
        return 1;
    }
    return 0;
}
