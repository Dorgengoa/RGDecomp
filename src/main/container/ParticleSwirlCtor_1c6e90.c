#include "types.h"

extern void NameTableNodeCtor_15ae50(s32);
extern void memset(s32, s32, s32);
extern void ParticleSwirlReset_17d750(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 ParticleSwirlCtor_1c6e90(s32 p0)
{
    u8 *l1;

    NameTableNodeCtor_15ae50((p0 + 0x20));
    l1 = (u8 *)p0 + 0x90;
    do {
        memset((s32)l1, 0, 0x20);
        l1 = l1 + 0x20;
    } while (l1 < (u8 *)p0 + 0x310);
    ParticleSwirlReset_17d750(p0);
    return p0;
}
