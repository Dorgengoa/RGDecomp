/* rgp:protos */
#define RGP_SELF_EvCmdSubScaleWait_262930 1
#include "port/game_protos.h"
#line 1
/* EvCmdSubScaleWait_262930 -- shape-identical to merged EvCmdSubMotionWait_263070 (23 instructions); the donor's
   source with the symbol renamed and 1 call target(s) substituted:
     EventSubNodeAddMotionWait_251360 -> EventSubNodeAddScaleWait_250f20
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/* One script-command handler out of an address-local family.  The
   operand stream is read 8 bytes at a time through three accessors;
   retail keeps a REAL incrementing cursor in a callee-saved register
   (daddu cur,a0 / addiu cur,8 in the jal delay slot), which is the
   POST-INCREMENT form f(p++).  Writing "f(p); p += 8;" instead lets
   mwcc fold every advance into base+offset addressing and the unit
   comes out one word short per operand. */

typedef struct SArg {
    s32 w[2];
} SArg;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdSubScaleWait_262930(SArg *p0)
{
    s32 a;
    s32 b;
    s32 r;
    s32 rv;

    a = ScriptGetInt_26a2a0(p0++);
    b = ScriptGetInt_26a2a0(p0);
    r = ((s32)EvtGetSubMachine_26abb0(a));
    rv = 1;
    if (r == 0) {
        rv = 0;
    } else {
        EventSubNodeAddScaleWait_250f20(r, b);
        rv = 1;
    }
    return rv;
}
