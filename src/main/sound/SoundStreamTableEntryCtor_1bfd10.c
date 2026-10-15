#include "types.h"

extern s32 SoundStreamCtor_1c0fd0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x7C];
    s32 m7C;
    u8 m80;
    u8 pad081[0x1];
    s16 m82;
};

struct Obj0 *SoundStreamTableEntryCtor_1bfd10(struct Obj0 *p0)
{
    s32 r0;

    r0 = SoundStreamCtor_1c0fd0(p0);
    p0->m7C = -1;
    p0->m80 = 0;
    p0->m82 = 0;
    return p0;
}
