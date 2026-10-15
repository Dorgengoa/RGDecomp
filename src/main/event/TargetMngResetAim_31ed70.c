#include "types.h"

extern void MatIdentity_1cbe40(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xF0];
    s32 mF0;
    u8 pad0F4[0x4C];
    s32 m140;
    s32 m144;
    s32 m148;
};

void TargetMngResetAim_31ed70(struct Obj0 *p0)
{
    MatIdentity_1cbe40((struct Obj0 *)((u8 *)p0 + 0x100));
    p0->m140 = 0;
    p0->m144 = 0x41A00000;
    p0->m148 = 0x41900000;
    p0->mF0 = 0;
}
