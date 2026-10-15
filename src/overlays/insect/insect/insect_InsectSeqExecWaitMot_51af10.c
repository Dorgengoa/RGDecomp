#include "types.h"
/* insect 0x0051AF10 -- 31 instructions.  The 0051AF90 shape with a float
 * tail: the `andi $2,$2,0xFF` on the computed exit and the bare `addiu 1` on
 * the early ones is a u8 return with a u8 local.  $f20 is loaded in the
 * `bnel` delay slot, so the member read belongs to the taken arm.  The outer
 * guard is NESTED so its arm falls through to the final `return 1`. */

typedef struct Obj {
    u8  pad00[0xC];
    f32 mC;                         /* +0x0C */
} Obj;

extern s32 func_31A8D0(void);
extern s32 insect_InsectBattleGetActorSlot_50db40(s32 a, s32 b);
extern f32 insect_InsectPieceGetMotionPhase_5142d0(s32 a);

u8 insect_InsectSeqExecWaitMot_51af10(Obj *p)
{
    s32 r;
    s32 h;
    f32 v;
    f32 t;
    s32 ret;

    r = func_31A8D0();
    if (p == 0 || r == 0) {
        return 1;
    }
    h = insect_InsectBattleGetActorSlot_50db40(r, 0);
    if (h == 0) {
        return 1;
    }
    v = p->mC;
    t = insect_InsectPieceGetMotionPhase_5142d0(h);
    ret = 1;
    if (t < v) {
        ret = 0;
    }
    return ret;
}
