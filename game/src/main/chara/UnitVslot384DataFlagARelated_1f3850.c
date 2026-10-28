/* rgp:protos */
#define RGP_SELF_UnitVslot384DataFlagARelated_1f3850 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x234];
    struct Obj1 *m234;
};

struct Obj1 {
    u8 pad000[0xA];
    u8 m0A;
};

u32 UnitVslot384DataFlagARelated_1f3850(struct Obj0 *p0)
{
    return (u8)((p0->m234->m0A & 1));
}
