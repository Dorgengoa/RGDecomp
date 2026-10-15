#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern s32 OptionsSetTacticsMode_3d5f50(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
};

s32 AiCmdOptionsSetTacticsMode_2c58c0(s32 p0)
{
    struct Obj0 *r0;
    s32 r1;
    s32 t0;
    s32 r2;

    r0 = GetGameData_1fede0();
    r1 = ScriptSlotGetInt_2cc9c0(p0);
    t0 = r0->m0C;
    r2 = OptionsSetTacticsMode_3d5f50(t0, r1);
    return 1;
}
