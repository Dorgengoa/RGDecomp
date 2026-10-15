#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00470560[];
extern u8 D_004705B0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x4C];
    void *m4C;
};

struct Obj0 *FuncDataRecCtor_190d30(struct Obj0 *p0)
{
    p0->m4C = D_004705B0;
    p0->m4C = D_00470560;
    return p0;
}
