#include "types.h"

/* One script-command handler out of an address-local family.  The
   operand stream is read 8 bytes at a time through three accessors;
   retail keeps a REAL incrementing cursor in a callee-saved register
   (daddu cur,a0 / addiu cur,8 in the jal delay slot), which is the
   POST-INCREMENT form f(p++).  Writing "f(p); p += 8;" instead lets
   mwcc fold every advance into base+offset addressing and the unit
   comes out one word short per operand. */

/* the float is ARGUMENT THREE: retail sets $f12 up between the $a1 and
   the $a2 move, and the EABI keeps the pools independent so
   (s32, s32, f32, s32) still gives $4/$5/$f12/$6. */

typedef struct SArg {
    s32 w[2];
} SArg;

extern s32 ScriptGetInt_26a2a0(SArg *);
extern f32 TaggedGetFloat_26a280(SArg *);
extern s32 EvtGetSubMachine_26abb0(s32);
extern s32 D_00482060;
extern s32 EventCameraNodeAddPlaceObjOnView_2537a0(s32, s32, f32, s32);

s32 EvCmdCameraPlaceObjOnView_263d30(SArg *p0)
{
    s32 a;
    f32 fv;
    s32 b;

    a = ScriptGetInt_26a2a0(p0++);
    fv = TaggedGetFloat_26a280(p0++);
    b = ScriptGetInt_26a2a0(p0);
    EventCameraNodeAddPlaceObjOnView_2537a0(D_00482060, a, fv, b);
    return 1;
}
