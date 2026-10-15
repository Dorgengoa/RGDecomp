#include "types.h"

extern void EffectResLoadPoll_2e15d0(void *);
extern void EffectEntryLoadPoll_2deba0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4078];
    s16 m4078;
};

void EffectMgrLoadPoll_2e3030(struct Obj0 *p0)
{
    s16 t0;

    t0 = p0->m4078;
    if (t0 != 0) {
        EffectResLoadPoll_2e15d0(p0);
        EffectEntryLoadPoll_2deba0((struct Obj0 *)((u8 *)p0 + 0x1674));
    }
}
