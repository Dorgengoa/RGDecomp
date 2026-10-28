/* rgp:protos */
#define RGP_SELF_insect_InsectBattleCamEyeRefresh_4f2fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F2FD0 -- 5 instructions, a tail call.  Both integer parameters
 * pass straight through ($4/$5 are never rewritten); the incoming float is
 * moved to $f15, i.e. it is the callee's LAST float parameter, and the three
 * loads fill $f12/$f13/$f14.  Under the PS2 EABI the GPR and FPR pools are
 * independent, so the float sits at parameter six. */

typedef struct Ins {
    u8  pad000[0x80];
    f32 m80;                        /* +0x80 */
    f32 m84;                        /* +0x84 */
    f32 m88;                        /* +0x88 */
} Ins;

/*rgp*/

void insect_InsectBattleCamEyeRefresh_4f2fd0(Ins *o, s32 k, f32 w)
{
    insect_InsectBattleCamEyeToCell_4f3150(o, k, o->m80, o->m84, o->m88, w);
}
