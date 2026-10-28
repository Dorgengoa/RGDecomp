/* rgp:protos */
#define RGP_SELF_HeapBlockRefCtor_30d990 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0047CCF0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    void *m0C;
};

struct Obj0 *HeapBlockRefCtor_30d990(struct Obj0 *p0)
{
    p0->m0C = D_0047CCF0;
    return p0;
}
