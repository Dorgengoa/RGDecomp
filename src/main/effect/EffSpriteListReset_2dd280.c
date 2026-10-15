#include "types.h"

extern void EffectInstanceReset_2dd410(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    u8 pad002[0x22E];
    s32 m230;
    s32 m234;
    s32 m238;
    s16 m23C;
    s16 m23E;
    u8 pad240[0x4];
    s32 m244;
    s16 m248;
};

void EffSpriteListReset_2dd280(struct Obj0 *p0)
{
    EffectInstanceReset_2dd410(p0);
    p0->m00 = 2;
    p0->m23C = -1;
    p0->m23E = -1;
    p0->m230 = -1;
    p0->m234 = -1;
    p0->m238 = -1;
    p0->m244 = 0;
    p0->m248 = -1;
}
