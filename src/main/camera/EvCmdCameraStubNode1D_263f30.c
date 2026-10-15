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
extern s32 EventCameraNodeAddStub1D_253950(s32, s32, f32, f32, f32);

/* retail falls THROUGH into the three float reads when p1 == 4
   (bnel p1,4 jumps past them), so that is the if body. */

s32 EvCmdCameraStubNode1D_263f30(SArg *p0, s32 p1)
{
    s32 a;
    f32 x;
    f32 y;
    f32 z;

    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    a = ScriptGetInt_26a2a0(p0++);
    if (p1 == 4) {
        x = TaggedGetFloat_26a280(p0++);
        y = TaggedGetFloat_26a280(p0++);
        z = TaggedGetFloat_26a280(p0);
    }
    EventCameraNodeAddStub1D_253950(D_00482060, a, x, y, z);
    return 1;
}
