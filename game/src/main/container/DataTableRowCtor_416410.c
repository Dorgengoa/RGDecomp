/* rgp:protos */
#define RGP_SELF_DataTableRowCtor_416410 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472250[];
extern u8 D_00479CB0[];
extern u8 D_0047AD30[];
extern u8 D_0047AD38[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    void *m04;
    u8 pad008[0x1C];
    void *m24;
};

struct Obj0 *DataTableRowCtor_416410(struct Obj0 *p0)
{
    p0->m04 = D_00472250;
    p0->m04 = D_00479CB0;
    p0->m24 = D_0047AD30;
    p0->m04 = D_0047AD38;
    return p0;
}
