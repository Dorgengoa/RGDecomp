/* rgp:protos */
#define RGP_SELF_insect_InsectAbilityTableCmdVariantMask_51c860 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051C860 -- 38 instructions.  The context global is _gp+0x0
 * (D_00485170), so it stays plain -- see insect_InsectAbilityTableCmdNextRecord_51c900.c.  The cursor is a
 * pointer walked by 8 per iteration, not an index, and the OR'd bit is an
 * explicit (u8) narrowing (`andi 0xFF` BEFORE the `or`).
 *
 * The second guard is NESTED: `beql $16,$0,<epilogue>` with `addiu $2,$0,1`
 * in the delay slot only comes out when that arm falls through to the
 * function's last `return 1`. */

typedef struct Obj {
    u8 pad00[0x70];
    u8 m70;                         /* +0x70 */
} Obj;

typedef struct Ctx {
    u8   pad00[0x64];
    Obj *m64;                       /* +0x64 */
} Ctx;

extern Ctx *D_00485170;
typedef struct E8 {
    s32 a;
    s32 b;
} E8;

/*rgp*/

s32 insect_InsectAbilityTableCmdVariantMask_51c860(E8 *p, s32 n)
{
    s32 i;
    Obj *o;
    Ctx *g;

    g = D_00485170;
    if (g == 0) {
        return 0;
    }
    o = g->m64;
    if (o != 0) {
        o->m70 = 0;
        for (i = 0; i < n; i++) {
            o->m70 = o->m70 | (u8)(1 << VariantGetInt_15f780(p++));
        }
    }
    return 1;
}
