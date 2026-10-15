#include "types.h"

typedef struct E8W { u8 b[8]; } E8W;

extern void * GetEntryTableGlobal_32c2e0(void);
extern s32 VariantGetInt_15f780(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x28];
    s16 m28;
    s16 m2A;
};

s32 EntryScriptCmdSetBlockSize_322770(s32 p0)
{
    struct Obj0 *r0;
    s32 r1;
    s32 r2;
    E8W *q;

    q = (E8W *)p0;
    r0 = GetEntryTableGlobal_32c2e0();
    if (r0 == 0) {
        return 0;
    }
    r1 = VariantGetInt_15f780((s32)q++);
    r2 = VariantGetInt_15f780((s32)q);
    r0->m28 = r1;
    r0->m2A = r2;
    return 1;
}
