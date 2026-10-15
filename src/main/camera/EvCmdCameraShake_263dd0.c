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
extern s32 D_00482060;
extern s32 EventCameraNodeAddShake_253840(s32, f32 *, s32);

s32 EvCmdCameraShake_263dd0(SArg *p0)
{
    f32 v[4];
    s32 b;

    v[0] = TaggedGetFloat_26a280(p0++);
    v[1] = TaggedGetFloat_26a280(p0++);
    v[2] = TaggedGetFloat_26a280(p0++);
    v[3] = 0.0f;
    b = ScriptGetInt_26a2a0(p0);
    EventCameraNodeAddShake_253840(D_00482060, v, b);
    return 1;
}
