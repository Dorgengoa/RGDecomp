#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472250[];
extern u8 D_00478590[];
extern u8 D_00478598[];
extern u8 D_00478620[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    void *m0C;
    u8 pad010[0x7C];
    void *m8C;
};

struct Obj0 *DataTableRowCtor_405350(struct Obj0 *p0)
{
    p0->m0C = D_00472250;
    p0->m0C = D_00478620;
    p0->m8C = D_00478590;
    p0->m0C = D_00478598;
    return p0;
}
