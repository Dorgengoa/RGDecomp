/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecMot_51b210 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051B210 -- 216 bytes.  A two-case dispatch on the phase word; both
 * `beql`s jump INTO their arm, so it is a switch and the compare chain runs the
 * cases in reverse ([[insect-dispatch-branch-polarity]]).  The 0x24 float is
 * loaded into $f20 BEFORE the call, so it is a named local. */

typedef struct Obj {
    u8  pad00[0x4];
    s32 f04;                        /* +0x04 */
    u8  pad08[0x0C - 0x08];
    u8  f0C[0x20 - 0x0C];           /* +0x0C */
    f32 f20;                        /* +0x20 */
    f32 f24;                        /* +0x24 */
    s32 f28;                        /* +0x28 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectSeqExecMot_51b210(Obj *o)
{
    void *g;
    void *h;
    f32   v;

    g = InsectBattleGet_31a8d0();
    if (o == 0 || g == 0) {
        return 1;
    }
    h = insect_InsectBattleGetActorSlot_50db40(g, 0);
    if (h == 0) {
        return 1;
    }
    switch (o->f04) {
    case 0:
        insect_InsectPieceMotionQueueClear_514320(h);
        insect_InsectPieceMotionQueuePush_514510(h, o->f0C, o->f28, o->f20, o->f24);
        o->f04 = o->f04 + 1;
        break;
    case 1:
        v = o->f24;
        if (insect_InsectPieceGetMotionPhase_5142d0(h) >= v) {
            return 1;
        }
        break;
    }
    return 0;
}
