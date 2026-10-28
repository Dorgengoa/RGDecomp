/* rgp:protos */
#define RGP_SELF_insect_InsectAbilityTableCmdSpecies_51ce00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vm_slot.h"
/* insect 0x0051CE00 -- the f_cbstore shape writing TWO byte fields.  The
 * `sb $2, 0x70($16)` of the 0xFF sits in the `jal`'s delay slot, which is what
 * a store written BEFORE the call produces; swapped, the call's argument setup
 * would take the slot and the store would follow the call. */
typedef struct CbObj {
    u8 pad00[0x60];
    u8 f60;            /* +0x60 */
    u8 pad61[0xF];
    u8 f70;            /* +0x70 */
} CbObj;

typedef struct CbCtx {
    u8 pad00[0x64];
    CbObj *f64;        /* +0x64 */
} CbCtx;

extern CbCtx *D_00485170;
/*rgp*/

s32 insect_InsectAbilityTableCmdSpecies_51ce00(Slot *v)
{
    CbCtx *g;
    CbObj *o;

    g = D_00485170;
    if (g == 0) {
        return 0;
    }
    o = g->f64;
    if (o != 0) {
        o->f70 = 0xFF;
        o->f60 = VariantGetInt_15f780(v);
    }
    return 0;
}
