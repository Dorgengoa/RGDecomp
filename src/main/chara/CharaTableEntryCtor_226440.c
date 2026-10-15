#include "types.h"

extern void CharaTableDataClear_227090(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x34];
    s32 m34;
    s16 m38;
    s16 m3A;
    s32 m3C;
    s32 m40;
};

struct Obj0 *CharaTableEntryCtor_226440(struct Obj0 *p0)
{
    CharaTableDataClear_227090(p0);
    CharaTableDataClear_227090(p0);
    p0->m34 = 0;
    p0->m38 = -1;
    p0->m3A = 0;
    p0->m3C = 0;
    p0->m40 = 0;
    return p0;
}
