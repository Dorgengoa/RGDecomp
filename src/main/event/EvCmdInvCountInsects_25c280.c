#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 InvCollectInsects_3c4d90(s32, void *, s32);
extern s32 ScriptSetRefInt_26a1e0(s32, s32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

s32 EvCmdInvCountInsects_25c280(s32 p0)
{
    u128 v20[64];
    struct Obj0 *r0;
    s32 t0;
    s32 r1;
    s32 r2;

    r0 = GetGameData_1fede0();
    t0 = r0->m18;
    r1 = InvCollectInsects_3c4d90(t0, v20, 0x100);
    r2 = ScriptSetRefInt_26a1e0(p0, r1);
    return 1;
}
