/* rgp:protos */
#define RGP_SELF_DataTableRowCtor_4051b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472250[];
extern u8 D_004785C0[];
extern u8 D_004785C8[];
extern u8 D_00478640[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    void *m0C;
    u8 pad010[0x28];
    void *m38;
};

struct Obj0 *DataTableRowCtor_4051b0(struct Obj0 *p0)
{
    p0->m0C = D_00472250;
    p0->m0C = D_00478640;
    p0->m38 = D_004785C0;
    p0->m0C = D_004785C8;
    return p0;
}
