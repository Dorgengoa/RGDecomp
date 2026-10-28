/* rgp:protos */
#define RGP_SELF_insect_InsectAbilityTableCmdMotionMaybe_51c9e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051C9E0 -- 128 bytes, 32 instructions, 3 calls.  Same context
 * global as 0x0051C860: _gp+0x0 = D_00485170, so it stays a plain extern
 * pointer.  Retail's `daddu $18,$4,$0` + `addiu $18,$18,0x8` is the PARAMETER
 * REASSIGNED, not a hoisted second local: a fresh local gives `addiu $18,$4,8`
 * and costs the move.  Member vs arithmetic form is inert here.  `n > 1` (not `n >= 2`) puts the compare in $at
 * ([[at-compare-class]]). */

typedef struct Obj {
    u8  pad00[0x20];
    u8  m20;                        /* +0x20 */
    u8  pad21[0x6C - 0x21];
    f32 m6C;                        /* +0x6C */
} Obj;

typedef struct Ctx {
    u8   pad00[0x64];
    Obj *m64;                       /* +0x64 */
} Ctx;

typedef struct Arg {
    u8  pad0[0x8];
    s32 m8;                         /* +0x08 */
} Arg;

extern Ctx *D_00485170;

/*rgp*/
extern void strcpy(u8 *p, s32 v);
/*rgp*/

s32 insect_InsectAbilityTableCmdMotionMaybe_51c9e0(Arg *a, s32 n)
{ __typeof__(a) rgp_entry_a = a;
    Ctx *g;
    Obj *o;

    g = D_00485170;
    if (g == 0) {
        return 0;
    }
    o = g->m64;
    if (o != 0) {
        a = (Arg *)((u8 *)a + 8);
        strcpy(&o->m20, SlotGetInt_15f720((void *)rgp_entry_a));
        if (n > 1) {
            o->m6C = VariantGetFloat_15f740((s32 *)a);
        }
        return 1;
    }
    return 0;
}
