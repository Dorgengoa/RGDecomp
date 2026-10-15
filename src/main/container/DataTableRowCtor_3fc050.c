#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472250[];
extern u8 D_00477110[];
extern u8 D_004773D0[];
extern u8 D_004773D8[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    void *m04;
    u8 pad008[0x24];
    void *m2C;
};

struct Obj0 *DataTableRowCtor_3fc050(struct Obj0 *p0)
{
    p0->m04 = D_00472250;
    p0->m04 = D_00477110;
    p0->m2C = D_004773D0;
    p0->m04 = D_004773D8;
    return p0;
}
