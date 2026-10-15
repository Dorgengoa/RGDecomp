#include "types.h"
#include "vm_slot.h"
/* insect 0x0051CDB0 -- the f_cbstore shape (insect_InsectAbilityTableCmdNeedsTarget_51cbd0) returning 1
 * on the success path instead of 0. */
typedef struct CbObj {
    u8 pad00[0x61];
    s8 f61;            /* +0x61 */
} CbObj;

typedef struct CbCtx {
    u8 pad00[0x64];
    CbObj *f64;        /* +0x64 */
} CbCtx;

extern CbCtx *D_00485170;
extern s32 func_15F780(Slot *v);

s32 insect_InsectAbilityTableCmdLevel_51cdb0(Slot *v)
{
    CbCtx *g;
    CbObj *o;

    g = D_00485170;
    if (g == 0) {
        return 0;
    }
    o = g->f64;
    if (o != 0) {
        o->f61 = func_15F780(v);
        return 1;
    }
    return 0;
}
