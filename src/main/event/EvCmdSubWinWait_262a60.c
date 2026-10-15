/* EvCmdSubWinWait_262a60 -- shape-identical to merged EvCmdSubMotionWait_263070 (23 instructions); the donor's
   source with the symbol renamed and 1 call target(s) substituted:
     EventSubNodeAddMotionWait_251360 -> EventSubNodeAddWinWait_250fc0
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

extern s32 ScriptGetInt_26a2a0(SArg *);
extern f32 TaggedGetFloat_26a280(SArg *);
extern s32 EvtGetSubMachine_26abb0(s32);
extern s32 EventSubNodeAddWinWait_250fc0(s32, s32);

s32 EvCmdSubWinWait_262a60(SArg *p0)
{
    s32 a;
    s32 b;
    s32 r;
    s32 rv;

    a = ScriptGetInt_26a2a0(p0++);
    b = ScriptGetInt_26a2a0(p0);
    r = EvtGetSubMachine_26abb0(a);
    rv = 1;
    if (r == 0) {
        rv = 0;
    } else {
        EventSubNodeAddWinWait_250fc0(r, b);
        rv = 1;
    }
    return rv;
}
