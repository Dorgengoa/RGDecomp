#include "types.h"

extern void CharaResetActionState_21ea00(void *);
extern void CharaMoveReqResetThunk_2194d0(void *);
extern void CharaSquashResetThunk_219300(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xA32];
    s16 mA32;
    u8 padA34[0x10];
    s32 mA44;
};

void CharaSetActionModeAppear_21c920(struct Obj0 *p0)
{
    s32 t0;

    p0->mA32 = 0x12;
    CharaResetActionState_21ea00(p0);
    CharaMoveReqResetThunk_2194d0((struct Obj0 *)((u8 *)p0 + 0x930));
    CharaSquashResetThunk_219300((struct Obj0 *)((u8 *)p0 + 0x950));
    t0 = p0->mA44;
    p0->mA44 = (t0 | 0x40000000);
}
