/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecRotate_518cc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00518CC0 -- 116 bytes, 29 instructions.  Same shape as the merged
 * insect_FUN_005196E0: the first two guards are ONE `if` joined by `||`.
 * `lwc1 $f1, -0x7418($28)` is main-image small data (_gp = 0x00485170), so the
 * symbol is D_0047DD58 and it must stay a non-const `f32` extern to keep the
 * %gp_rel relocation.  `mul.s $f12, $f1, $f0` puts the constant on the LEFT;
 * `lwc1 $f2,0x10($16)` + `cvt.s.w` is an s32 member converted to float. */

typedef struct Obj {
    u8  pad00[0x0C];
    f32 f0C;                        /* +0x0C */
    s32 f10;                        /* +0x10 */
} Obj;

extern f32 D_0047DD58;

/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectSeqExecRotate_518cc0(Obj *o)
{
    s32 h;

    h = InsectBattleGet_31a8d0();
    if (o == 0 || h == 0) {
        return 1;
    }
    h = insect_InsectBattleGetActorSlot_50db40(h, 0);
    if (h == 0) {
        return 1;
    }
    insect_InsectPieceSetYawOffsetTarget_515350(h, D_0047DD58 * o->f0C, (f32)o->f10);
    return 1;
}
