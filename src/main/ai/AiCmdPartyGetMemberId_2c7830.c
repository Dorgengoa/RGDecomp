#include "types.h"

typedef struct E8W { u8 b[8]; } E8W;

extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern void * GetGameData_1fede0(void);
extern s32 PartyGetMemberId_3c2490(s32, s32);
extern void ScriptSlotStoreIntRef_2cc900(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

s32 AiCmdPartyGetMemberId_2c7830(s32 p0, s32 p1)
{
    E8W *q;
    s32 r0;
    struct Obj0 *r1;
    s32 t0;
    s32 r2;

    q = (E8W *)p0;
    if (p1 != 2) {
        return 0;
    }
    r0 = ScriptSlotGetInt_2cc9c0((s32)q++);
    r1 = (struct Obj0 *)GetGameData_1fede0();
    t0 = r1->m18;
    r2 = PartyGetMemberId_3c2490(t0, r0);
    ScriptSlotStoreIntRef_2cc900((s32)q, r2);
    return 1;
}
