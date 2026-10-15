#include "types.h"

extern void StoreU32Bytes_302ef0(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x60];
    u16 m60;
    u8 pad062[0x6];
    s16 m68;
};

void CharaEffEntrySetRefFrm_230140(struct Obj0 *p0, s32 p1, s32 p2)
{
    u16 t0;

    t0 = p0->m60;
    p0->m60 = (t0 | 0x80);
    p0->m68 = p1;
    StoreU32Bytes_302ef0((struct Obj0 *)((u8 *)p0 + 0x64), p2);
}
