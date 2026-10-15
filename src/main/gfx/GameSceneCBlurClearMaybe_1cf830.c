#include "types.h"

extern void CBlurTexClearMaybe_179020(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x58B0];
    s8 m58B0;
};

void GameSceneCBlurClearMaybe_1cf830(struct Obj0 *p0)
{
    s8 t0;

    t0 = p0->m58B0;
    if (t0 != 0) {
        CBlurTexClearMaybe_179020((struct Obj0 *)((u8 *)p0 + 0x58C0));
    }
}
