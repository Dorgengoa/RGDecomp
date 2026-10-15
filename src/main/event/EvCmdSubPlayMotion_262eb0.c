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
extern s32 ScriptGetCodeAddr_26a200(SArg *);
extern s32 EventSubNodeAddPlayMotion_251280(s32, s32, s32, f32);

s32 EvCmdSubPlayMotion_262eb0(SArg *p0, s32 p1)
{
    s32 a;
    s32 c;
    s32 b;
    s32 r;
    s32 rv;
    f32 fv;

    c = 0;
    fv = -1.0f;
    a = ScriptGetInt_26a2a0(p0++);
    b = ScriptGetCodeAddr_26a200(p0++);
    if (p1 >= 3) {
        c = ScriptGetInt_26a2a0(p0++);
    }
    if (p1 >= 4) {
        fv = TaggedGetFloat_26a280(p0);
    }
    r = EvtGetSubMachine_26abb0(a);
    rv = 1;
    if (r == 0) {
        rv = 0;
    } else {
        EventSubNodeAddPlayMotion_251280(r, b, c, fv);
        rv = 1;
    }
    return rv;
}
