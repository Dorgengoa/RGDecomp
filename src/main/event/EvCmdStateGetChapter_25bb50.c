#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 StateGetChapter_3cd5b0(s32);
extern s32 ScriptSetRefInt_26a1e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

s32 EvCmdStateGetChapter_25bb50(s32 p0)
{
    struct Obj0 *r0;
    s32 t0;
    s32 r1;
    s32 r2;

    r0 = GetGameData_1fede0();
    t0 = r0->m10;
    r1 = StateGetChapter_3cd5b0(t0);
    r2 = ScriptSetRefInt_26a1e0(p0, r1);
    return 1;
}
