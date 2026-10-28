/* rgp:protos */
#define RGP_SELF_CharaCmdFadeIn_22bb10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* `slti $1` (i.e. $at) feeding a `bnez` is the [[at-compare-class]] tell: the
   source wrote `> K-1`, not `>= K`.

Event-script command handler.  Guard read off the listing:
   beq $6,1 -> body, beql $6,2 -> body(join+4) with the join's `slti`
   duplicated into the branch-likely delay slot, fall-through = return 0.
   That is `if (argc != 1 && argc != 2) return 0;`.
   `slti $1,$6,2 / bnez $1` is a PLAIN branch with `addiu $2,$0,-1` in the
   delay slot, so the -1 is unconditional and the call is a plain `if`. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    s32 m00;
};

s32 CharaCmdFadeIn_22bb10(struct Obj0 *p0, s32 p1, s32 argc)
{
    s32 a;
    s32 x;
    s32 y;
    s32 z;

    if (argc != 1 && argc != 2) {
        return 0;
    }
    a = -1;
    if (argc > 1) {
        a = ScriptArgGetInt_302d70(p1 + 5);
    }
    x = ObjIdResolveAlias_1ce490(p0->m00, a);
    y = GetCurrentScene_1f5be0();
    z = ScriptArgGetInt_302d70(p1);
    ParamTableFadeToOne_1cf9e0(y, x, z);
    return 1;
}
