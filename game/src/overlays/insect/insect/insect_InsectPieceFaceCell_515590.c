/* rgp:protos */
#define RGP_SELF_insect_InsectPieceFaceCell_515590 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00515590 -- 312 bytes, 78 instructions.  Reads the object's
 * position into buf, scales x/z by 1/4, aims the object at (x, y) from the
 * grid cell (2, 3) and hands the angle (degrees) and the speed z to
 * insect_InsectPieceSetYawTarget_5156d0.  An exact zero offset in both axes returns early.
 *
 * The two file-scope register bindings are the ONLY spelling that puts the
 * 2.0f carrier in $a2 (retail) instead of $a0: an object bound to a register
 * enters mwcc's EXIT SEED (CodeGen.c FUN_00436970), so $a0/$a1 are live on
 * the early-return path through the float block and the lowest-free colour
 * after $v0 (seed) and $v1 (3.0f) is $a2.  The binding must be declared with
 * the pragma ON and the pragma must be OFF again before the function, or
 * RegisterInfo.c rejects a volatile register ("global register variable
 * assigned to volatile register").  Declared `extern` so no .sbss symbol is
 * emitted; the object's sections and symbols are identical to the unbound
 * build.  See build/ix95/FINDINGS.md. */

#pragma vu0_mmi_reg_binding on
extern s32 gq asm("r4");
extern s32 gr asm("r5");
#pragma vu0_mmi_reg_binding off

typedef struct Obj { u8 pad00[0x71]; s8 f71; } Obj;

extern f32 D_0047D1FC;                      /* pi, gp - 0x7F74 */

/*rgp*/
/*rgp*/
/*rgp*/             /* fptodp */
/*rgp*/      /* atan2 (f64, f64) */
/*rgp*/             /* dptofp */

void insect_InsectPieceFaceCell_515590(Obj *o, f32 x, f32 y, f32 z)
{
    f32 buf[4] __attribute__((aligned(16)));
    f32 dx;
    f32 dy;

    insect_InsectPieceGetPos_5150d0(o, buf, 0, 0);
    buf[0] = buf[0] / 4.0f;
    buf[2] = buf[2] / 4.0f;
    dx = x - (2.0f + buf[0]);
    dy = y - (3.0f + buf[2]);
    if (!dx && !dy) {
        return;
    }
    if (o->f71 == 0) {
        dx = dx * -1.0f;
        dy = dy * -1.0f;
    }
    insect_InsectPieceSetYawTarget_5156d0(o,
        180.0f * dptofp(Atan2_129148(fptodp(dx), fptodp(dy))) / D_0047D1FC,
        z);
}
