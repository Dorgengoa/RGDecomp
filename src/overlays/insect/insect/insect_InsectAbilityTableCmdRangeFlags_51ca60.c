#include "types.h"
/* insect 0x0051CA60 -- 84 bytes, 21 instructions, 1 call.  The 0x0051CAC0
 * family with a flag byte at +0x69 and a `return 1` on the hit path: the gp
 * global D_00485170 is _gp+0x0 and stays a plain extern, and the
 * `andi $4,$2,0xFF` is the u8 narrowing of the s32 result before the OR.
 */

typedef struct CbObj {
    u8 pad00[0x69];
    u8 f69;            /* +0x69 */
} CbObj;

typedef struct CbCtx {
    u8     pad00[0x64];
    CbObj *f64;        /* +0x64 */
} CbCtx;

typedef struct Slot { u8 raw[8]; } Slot;

extern CbCtx *D_00485170;
extern s32 func_15F780(Slot *v);

s32 insect_InsectAbilityTableCmdRangeFlags_51ca60(Slot *v)
{
    CbCtx *g;
    CbObj *o;

    g = D_00485170;
    if (g == 0) {
        return 0;
    }
    o = g->f64;
    if (o != 0) {
        o->f69 = o->f69 | (u8)func_15F780(v);
        return 1;
    }
    return 0;
}
