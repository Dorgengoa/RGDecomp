/* rgp:protos */
#define RGP_SELF_DataTableRowCtor_405010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472250[];
extern u8 D_004785F0[];
extern u8 D_004785F8[];
extern u8 D_00478660[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    void *m04;
    u8 pad008[0x14];
    void *m1C;
};

struct Obj0 *DataTableRowCtor_405010(struct Obj0 *p0)
{
    p0->m04 = D_00472250;
    p0->m04 = D_00478660;
    p0->m1C = D_004785F0;
    p0->m04 = D_004785F8;
    return p0;
}
