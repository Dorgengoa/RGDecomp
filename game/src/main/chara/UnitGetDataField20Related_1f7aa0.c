/* rgp:protos */
#define RGP_SELF_UnitGetDataField20Related_1f7aa0 1
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
    u8 pad000[0x20];
    s32 m20;
};

s32 UnitGetDataField20Related_1f7aa0(struct Obj0 *p0)
{
    return p0->m234->m20;
}
