/* rgp:protos */
#define RGP_SELF_EvCmdSubSplineMove_2637b0 1
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

typedef struct SArg {
    s32 w[2];
} SArg;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* the optional read sits AFTER the abb0 call: its guard is a plain bnez
   with an EMPTY delay slot, not the bnel of the operand-count guards. */

s32 EvCmdSubSplineMove_2637b0(SArg *p0, s32 p1)
{
    s32 a;
    s32 r;
    s32 b;
    s32 rv;

    b = 0;
    a = ScriptGetInt_26a2a0(p0++);
    r = ((s32)EvtGetSubMachine_26abb0(a));
    if (p1 >= 2) {
        b = ScriptGetInt_26a2a0(p0);
    }
    rv = 1;
    if (r == 0) {
        rv = 0;
    } else {
        EventSubNodeAddSplineMove_251720(r, b);
        rv = 1;
    }
    return rv;
}
