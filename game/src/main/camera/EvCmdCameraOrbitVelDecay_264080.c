/* rgp:protos */
#define RGP_SELF_EvCmdCameraOrbitVelDecay_264080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* One script-command handler out of an address-local family.  The
   operand stream is read 8 bytes at a time through three accessors;
   retail keeps a REAL incrementing cursor in a callee-saved register
   (daddu cur,a0 / addiu cur,8 in the jal delay slot), which is the
   POST-INCREMENT form f(p++).  Writing "f(p); p += 8;" instead lets
   mwcc fold every advance into base+offset addressing and the unit
   comes out one word short per operand. */

/* the float is ARGUMENT TWO: retail sets $f12 up BEFORE the $a1 move
   that lands in the delay slot, and the EABI keeps the GPR and FPR pools
   independent so (s32, f32, s32) still gives $4/$f12/$5. */

typedef struct SArg {
    s32 w[2];
} SArg;

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00482060;
/*rgp*/

s32 EvCmdCameraOrbitVelDecay_264080(SArg *p0)
{
    f32 fv;
    s32 a;

    fv = TaggedGetFloat_26a280(p0++);
    a = ScriptGetInt_26a2a0(p0);
    EventCameraNodeAddOrbitVelDecay_253a90(D_00482060, a, fv);
    return 1;
}
