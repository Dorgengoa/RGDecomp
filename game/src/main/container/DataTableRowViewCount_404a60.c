/* rgp:protos */
#define RGP_SELF_DataTableRowViewCount_404a60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x16];
    s8 m16;
};

s64 DataTableRowViewCount_404a60(struct Obj0 *p0)
{
    return ((((s64)p0->m16) << 0x3C) >> 0x3C);
}
