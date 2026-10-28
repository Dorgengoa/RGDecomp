/* rgp:protos */
#define RGP_SELF_DataTableRowCtor_423000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472250[];
extern u8 D_0047BB90[];
extern u8 D_0047C290[];
extern u8 D_0047C298[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    void *m04;
    u8 pad008[0x14];
    void *m1C;
};

struct Obj0 *DataTableRowCtor_423000(struct Obj0 *p0)
{
    p0->m04 = D_00472250;
    p0->m04 = D_0047BB90;
    p0->m1C = D_0047C290;
    p0->m04 = D_0047C298;
    return p0;
}
