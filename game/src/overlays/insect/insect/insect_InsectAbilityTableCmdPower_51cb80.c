/* rgp:protos */
#define RGP_SELF_insect_InsectAbilityTableCmdPower_51cb80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vm_slot.h"
/* insect 0x0051CB80 -- the f_cbstore shape (insect_InsectAbilityTableCmdNeedsTarget_51cbd0) storing a
 * HALFWORD at +0x6A instead of a byte. */
typedef struct CbObj {
    u8 pad00[0x6A];
    s16 f6A;           /* +0x6A */
} CbObj;

typedef struct CbCtx {
    u8 pad00[0x64];
    CbObj *f64;        /* +0x64 */
} CbCtx;

extern CbCtx *D_00485170;
/*rgp*/

s32 insect_InsectAbilityTableCmdPower_51cb80(Slot *v)
{
    CbCtx *g;
    CbObj *o;

    g = D_00485170;
    if (g == 0) {
        return 0;
    }
    o = g->f64;
    if (o != 0) {
        o->f6A = VariantGetInt_15f780(v);
    }
    return 0;
}
