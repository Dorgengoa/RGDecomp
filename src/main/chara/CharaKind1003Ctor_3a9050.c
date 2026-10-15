#include "types.h"

extern s32 CharaBaseCtor_3a9190(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472CC0[];
extern u8 D_004731D0[];

struct Obj0;

struct Obj0 {
    void *m00;
};

struct Obj0 *CharaKind1003Ctor_3a9050(struct Obj0 *p0)
{
    s32 r0;

    r0 = CharaBaseCtor_3a9190(p0);
    p0->m00 = D_004731D0;
    p0->m00 = D_00472CC0;
    return p0;
}
